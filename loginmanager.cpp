#include "loginmanager.h"
#include <QRegularExpression>
#include <QTimer>

const QString LoginManager::AUTH_URL = "https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar";

LoginManager::LoginManager(QObject *parent)
    : QObject{parent},
      m_loadedHandler{nullptr},
      m_isLoggedIn{false},
      m_hasLoginErrors{false}
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
    emit webViewChanged();
}

void LoginManager::login(QString ssn, QString password)
{
    static QRegularExpression regex("[^\\d]");
    m_currentSsn = ssn.remove(regex);
    m_currentPassword = password;
    setLoginError(false);
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
    m_loadedHandler = &LoginManager::fillLoginInfo;

    if (m_isLoggedIn) {
        logout();
    } else {
        m_webView->setUrl(QUrl(AUTH_URL));
    }
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
    m_loadedHandler = &LoginManager::checkAfterLoginAttempt;
    m_webView->runJavaScript(script);
}

void LoginManager::checkAfterLoginAttempt()
{
    if (m_webView->url().toString().contains("authz")) {
        QObject::disconnect(m_webView, nullptr, this, nullptr);
        m_engine.globalObject().setProperty("isSessionInitialized", QJSValue(false));
        m_loadedHandler = nullptr;
        setLoginError(true);
        return;
    }

    QJSValue callback = m_engine.evaluate("(function(result) { isSessionInitialized = result; })");
    m_webView->runJavaScript("(function() {"
                             "  const btn = document.querySelector('button.button');"
                             "  if (btn.innerText.startsWith('Encerrar')) {"
                             "      return true;"
                             "  } else {"
                             "      return false;"
                             "  }"
                             "})()", callback);

    QTimer::singleShot(500, this, [this]() {
        if (m_engine.globalObject().property("isSessionInitialized").toBool()) {
            m_loadedHandler = &LoginManager::fillLoginInfo;
            m_webView->runJavaScript("document.querySelector('button.button').click()");
        } else {
            QObject::disconnect(m_webView, nullptr, this, nullptr);
            m_engine.globalObject().setProperty("isSessionInitialized", QJSValue(false));
            m_loadedHandler = nullptr;
            m_isLoggedIn = true;
            emit successfullyLoggedIn();
        }
    });
}
