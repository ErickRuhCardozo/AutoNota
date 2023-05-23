#include "loginmanager.h"
#include "qregularexpression.h"
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
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &LoginManager::loadChanged);
    emit webViewChanged();
}

void LoginManager::login(QString ssn, QString password)
{
    if (m_isLoggedIn) {
        logout();
    }

    m_currentSsn = ssn;
    m_currentPassword = password;
    this->m_loadedHandler = &LoginManager::fillLoginInfo;
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
    this->m_loadedHandler = &LoginManager::checkForInitializedSession;
    m_webView->runJavaScript(script);
}

void LoginManager::checkForInitializedSession()
{
    m_webView->runJavaScript("const btn = document.querySelector('button.button');"
                             "if (btn.innerText.startsWith('Encerrar'))"
                             "  btn.click();");
    // TODO
}
