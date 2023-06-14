#include "loginmanager.h"
#include <QRegularExpression>
#include <QTimer>

const QString LoginManager::AUTH_URL = "https://notaparana.pr.gov.br/nfprweb/ContaCorrente";

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

void LoginManager::setWebView(QQuickWebEngineView* newWebView)
{
    if (m_webView == newWebView)
        return;

    m_webView = newWebView;
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
    emit webViewChanged();
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

QString LoginManager::status() const
{
    return m_status;
}

void LoginManager::setStatus(const QString& newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

void LoginManager::login(const QString& user, const QString& ssn, const QString& password)
{
    emit loginRequested();
    setStatus(QString("Logando usuário %1").arg(user));
    static QRegularExpression regex("[^\\d]");
    QString unmaskedSsn = ssn;
    m_currentSsn = unmaskedSsn.remove(regex);
    m_currentPassword = password;
    setLoginError(false);
    m_loadedHandler = &LoginManager::fillLoginInfo;

    if (m_isLoggedIn) {
        logout();
    } else {
        m_webView->setUrl(QUrl(AUTH_URL));
    }
}

void LoginManager::logout()
{
    setStatus("Saindo...");
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
    setStatus("Preenchendo informações de login");
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
        setStatus("Falha na autenticação");
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
            setStatus("Finalizando Seção Ativa, aguarde...");
            m_loadedHandler = &LoginManager::fillLoginInfo;
            m_webView->runJavaScript("document.querySelector('button.button').click()");
        } else {
            m_loadedHandler = nullptr;
            m_isLoggedIn = true;
            setStatus("Logado com sucesso!");
            emit successfullyLoggedIn();
            QTimer::singleShot(2000, this, [this]() { setStatus(""); });
        }
    });
}
