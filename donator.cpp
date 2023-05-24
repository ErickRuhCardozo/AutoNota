#include "donator.h"

Donator::Donator(QObject *parent)
    : QObject{parent}
{

}

QQuickWebEngineView *Donator::webView() const
{
    return m_webView;
}

void Donator::setWebView(QQuickWebEngineView *newWebView)
{
    if (m_webView == newWebView)
        return;
    m_webView = newWebView;
    emit webViewChanged();
}

void Donator::startDonations()
{
    prepareForDonations();
}

void Donator::prepareForDonations()
{
    if (!isInDonationPage()) {
        m_webView->setUrl(QUrl("https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar"));
    }
}

bool Donator::isInDonationPage()
{
    QString url = m_webView->url().toString();
    return url.contains("DoacaoDocumentoFiscalCadastrar");
}
