#include "loginmanager.h"
#include <QRegularExpression>
#include <QTimer>

const QString LoginManager::AUTH_URL = "https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar";

LoginManager::LoginManager(QObject *parent)
    : QObject{parent},
      m_loadedHandler{nullptr},
      m_isLoggedIn{false},
    m_hasLoginErrors{false},
      m_skipCheckAfterLogin{false}
{
}

bool LoginManager::isLoggedIn() const
{
    return m_isLoggedIn;
}

QQuickWebEngineView *LoginManager::webView() const
{
    return m_webView;
}

bool LoginManager::hasLoginErrors() const
{
    return m_hasLoginErrors;
}

void LoginManager::setLoginError(bool error)
{
    m_hasLoginErrors = error;
    emit hasLoginErrorsChanged();
}

void LoginManager::setWebView(QQuickWebEngineView *newWebView)
{
    if (m_webView == newWebView)
        return;

    m_webView = newWebView;
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
    emit webViewChanged();
}

void LoginManager::login(QString ssn, QString password)
{
    if (m_isLoggedIn) {
        logout();
    }

    static QRegularExpression regex("[^\\d]");
    m_currentSsn = ssn.remove(regex);
    m_currentPassword = password;
    m_isLoggedIn = false;
    m_skipCheckAfterLogin = false;
    setLoginError(false);
    m_loadedHandler = &LoginManager::fillLoginInfo;
    m_webView->setUrl(QUrl(AUTH_URL));
}

void LoginManager::logout()
{
    m_isLoggedIn = false;
    m_webView->runJavaScript("document.querySelector('#user-logout').click()");
}

void LoginManager::loadChanged(const QWebEngineLoadingInfo& info)
{
    if (info.status() != QWebEngineLoadingInfo::LoadSucceededStatus)
        return;

    if (m_loadedHandler != nullptr)
        (this->*m_loadedHandler)();
}

void LoginManager::fillLoginInfo()
{    
    QString script = QString("document.querySelector('#attribute').value = '%1';"
                             "document.querySelector('#password').value = '%2';"
                             "document.querySelector('input[type=submit]').click();")
                    .arg(m_currentSsn, m_currentPassword);

    if (m_skipCheckAfterLogin) {
        m_loadedHandler = &LoginManager::checkFinalizedSession;
    } else {
        m_loadedHandler = &LoginManager::checkAfterLogin;
    }

    m_webView->runJavaScript(script);
}

void LoginManager::checkAfterLogin()
{
//    QString url = m_webView->url().toString();

//    if (url.contains("nfprweb/DoacaoDocumentoFiscalCadastrar")) { // Session Initialized. Finish it.
//        m_webView->runJavaScript("const btn = document.querySelector('button.button');"
//                                 "btn.innerText.startsWith('Encerrar') && btn.click()");
//        m_loadedHandler = &LoginManager::checkFinalizedSession;
//    } else { // Wrong Login Info. Signalize User.
//        setLoginError(true);
//    }
    QJSValue callback = m_engine.evaluate("(function(result) { isSessionInitialized = result; })");
    m_webView->runJavaScript("(function() {"
                             "  const btn = document.querySelector('button.button');"
                             "  if (btn.innerText.startsWith('Encerrar')) {"
                             "      btn.click();"
                             "      return true;"
                             "  } else {"
                             "      return false;"
                             "  }"
                             "})()", callback);
    QTimer::singleShot(500, this, [this]() {
        qDebug() << m_engine.globalObject().property("isSessionInitialized").toString();
    });
}

void LoginManager::checkFinalizedSession()
{
    QString url = m_webView->url().toString();

    if (url.contains("authz.identidadedigital.pr.gov.br")) {
        // We attempt to login in, but a session was already initialized.
        // At this point we know for sure that the session was finalized by checkAfterLogin()
        // So we can fill the login info again
        m_skipCheckAfterLogin = true;
        fillLoginInfo();
    } else if (url.contains("nfprweb/ContaCorrente")) {
        m_skipCheckAfterLogin = false;
        m_isLoggedIn = true;
        QObject::disconnect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
        m_loadedHandler = nullptr;
        emit successfullyLoggedIn();
    }
}
