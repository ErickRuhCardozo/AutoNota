#include "donationmanager.h"

DonationManager::DonationManager(QObject *parent)
    : QObject{parent},
    m_loadedHandler{nullptr},
    m_isPrepared{false},
    m_scanned{0},
    m_donated{0},
    m_rejected{0}
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
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &DonationManager::loadChanged);
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
    setScanned(m_scanned + 1);
}

void DonationManager::disconnect()
{
    m_loadedHandler = nullptr;
    m_isPrepared = false;
}

void DonationManager::donate()
{
    if (m_accessKeys.size() < 1)
        return;

    verifyDonation();

    QString accessKey = m_accessKeys.dequeue();
    QString script = QString("document.querySelector('#cnpjEntidade').value = '%1';"
                             "document.querySelector('#chaveAcesso').value = '%2';"
                             "document.querySelector('#btnDoarDocumento').click();")
                    .arg(m_cnpj, accessKey);
    m_webView->runJavaScript(script);
}

void DonationManager::verifyDonation()
{
    QString url = m_webView->url().toString();

    if (url.contains("_erro")) {
        setRejected(m_rejected + 1);
    } else if (url.contains("_mensagem")) {
        setDonated(m_donated + 1);
    }
}

void DonationManager::setScanned(int scanned)
{
    m_scanned = scanned;
    emit scannedChanged();
}

void DonationManager::setDonated(int donated)
{
    m_donated = donated;
    emit donatedChanged();
}

void DonationManager::setRejected(int rejected)
{
    m_rejected = rejected;
    emit rejectedChanged();
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
    m_webView->setUrl(QUrl("https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar"));
    m_isPrepared = true;
}

int DonationManager::scanned() const
{
    return m_scanned;
}

int DonationManager::donated() const
{
    return m_donated;
}

int DonationManager::rejected() const
{
    return m_rejected;
}
