#include "loginmanager.h"
#include <qquickwebengine_accessible.h>

const QString LoginManager::AUTH_URL = "https://notaparana.pr.gov.br/nfprweb";

LoginManager::LoginManager(QObject *parent)
    : QObject{parent}
{
    this->m_loadedHandler = NULL;
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
    emit webViewChanged();
}

void LoginManager::login(QString ssn, QString password)
{
    if (m_isLoggedIn) {
        logout();
    }

    m_currentSsn = ssn;
    m_currentPassword = password;
    m_isLoggedIn = false;
    m_skipInitializedSessionHandler = false;
    this->m_loadedHandler = &LoginManager::fillLoginInfo;
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
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

    if (this->m_loadedHandler != NULL)
        (this->*m_loadedHandler)();
}

void LoginManager::fillLoginInfo()
{    
    QString script = QString("document.querySelector('#attribute').value = '%1';"
                             "document.querySelector('#password').value = '%2';"
                             "document.querySelector('input[type=submit]').click();")
                    .arg(m_currentSsn, m_currentPassword);

    if (m_skipInitializedSessionHandler) {
        this->m_loadedHandler = &LoginManager::checkFinalizedSession;
    } else {
        this->m_loadedHandler = &LoginManager::handleInitializedSession;
    }

    m_webView->runJavaScript(script);
}

void LoginManager::handleInitializedSession()
{
    m_webView->runJavaScript("const btn = document.querySelector('button.button');"
                             "btn.innerText.startsWith('Encerrar') && btn.click()");
    this->m_loadedHandler = &LoginManager::checkFinalizedSession;
}

void LoginManager::checkFinalizedSession()
{
    QString url = m_webView->url().toString();

    if (url.contains("authz.identidadedigital.pr.gov.br")) {
        // We attempt to login in, but a session was already initialized.
        // At this point we know for sure that the session was finalized by checkForInitializedSession()
        // So we can fill the login info again
        m_skipInitializedSessionHandler = true;
        fillLoginInfo();
    } else if (url.contains("nfprweb/ContaCorrente")) {
        m_skipInitializedSessionHandler = false;
        m_isLoggedIn = true;
        QObject::disconnect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
        emit successfullyLoggedIn();
    }
}
