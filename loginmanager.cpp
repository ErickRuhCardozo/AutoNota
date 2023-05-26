#include "loginmanager.h"
#include "qregularexpression.h"
#include <qquickwebengine_accessible.h>

const QString LoginManager::AUTH_URL = "https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar";

LoginManager::LoginManager(QObject *parent)
    : QObject{parent}
{
    m_loadedHandler = NULL;
}

bool LoginManager::isLoggedIn() const
{
    return m_isLoggedIn;
}

QQuickWebEngineView *LoginManager::webView() const
{
    return m_webView;
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

    m_currentSsn = ssn.remove(QRegularExpression("[^\\d]"));
    m_currentPassword = password;
    m_isLoggedIn = false;
    m_skipCheckAfterLogin = false;
    m_loadedHandler = &LoginManager::fillLoginInfo;
    m_webView->setUrl(QUrl(AUTH_URL));
}

void LoginManager::logout()
{
    // TODO
}

void LoginManager::loadChanged(const QWebEngineLoadingInfo& info)
{
    if (info.status() != QWebEngineLoadingInfo::LoadSucceededStatus)
        return;

    if (m_loadedHandler != NULL)
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
    QString url = m_webView->url().toString();

    if (url.contains("nfprweb/DoacaoDocumentoFiscalCadastrar")) { // Session Initialized. Finish it.
        m_webView->runJavaScript("const btn = document.querySelector('button.button');"
                                 "btn.innerText.startsWith('Encerrar') && btn.click()");
        m_loadedHandler = &LoginManager::checkFinalizedSession;
    } else { // Wrong Login Info. Signalize User.
        m_webView->runJavaScript("alert('CPF ou Senha Inválidos.\\nRecomenda-se remover o usuário e cadastra-lo novamente com as informações corretas.')");
    }
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
        emit successfullyLoggedIn();
    }
}
