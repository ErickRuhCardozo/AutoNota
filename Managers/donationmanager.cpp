#include "donationmanager.h"

DonationManager::DonationManager(QObject *parent)
    : QObject{parent},
    m_loadedHandler{nullptr},
    m_isPrepared{false}
{
}

QQuickWebEngineView *DonationManager::webView() const
{
    return m_webView;
}

void DonationManager::setWebView(QQuickWebEngineView *newWebView)
{
    if (m_webView == newWebView)
        return;
    m_webView = newWebView;
    emit webViewChanged();
}


QString DonationManager::cnpj() const
{
    return m_cnpj;
}

void DonationManager::setCnpj(const QString &newCnpj)
{
    if (m_cnpj == newCnpj)
        return;
    m_cnpj = newCnpj;
    emit cnpjChanged();
}

void DonationManager::addAccessKey(const QString &accessKey)
{
    if (m_isPrepared && m_accessKeys.size() < 1)
        m_webView->reload();

    m_accessKeys.enqueue(accessKey);
}

void DonationManager::disconnect()
{
    m_isPrepared = false;
    QObject::disconnect(m_webView, nullptr, this, nullptr);
}

void DonationManager::donate()
{
    if (m_accessKeys.size() < 1)
        return;

    QString accessKey = m_accessKeys.dequeue();
    QString script = QString("document.querySelector('#cnpjEntidade').value = '%1';"
                             "document.querySelector('#chaveAcesso').value = '%2';"
                             "document.querySelector('#btnDoarDocumento').click();")
                    .arg(m_cnpj, accessKey);
    m_webView->runJavaScript(script);
}

void DonationManager::loadChanged(const QWebEngineLoadingInfo &info)
{
    if (info.status() != QWebEngineLoadingInfo::LoadSucceededStatus)
        return;

    if (m_loadedHandler != nullptr)
        (this->*m_loadedHandler)();
}

void DonationManager::prepareForDonations()
{
    m_loadedHandler = &DonationManager::donate;
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &DonationManager::loadChanged);
    m_webView->setUrl(QUrl("https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar"));
    m_isPrepared = true;
}
