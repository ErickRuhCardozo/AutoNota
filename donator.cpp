#include "donator.h"

Donator::Donator(QObject *parent)
    : QObject{parent},
    m_loadedHandler{nullptr}
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


QString Donator::cnpj() const
{
    return m_cnpj;
}

void Donator::setCnpj(const QString &newCnpj)
{
    if (m_cnpj == newCnpj)
        return;
    m_cnpj = newCnpj;
    emit cnpjChanged();
}

void Donator::addAccessKey(const QString &accessKey)
{
    if (m_accessKeys.size() < 1)
        m_webView->reload();

    m_accessKeys.enqueue(accessKey);
}

void Donator::disconnect()
{
    QObject::disconnect(m_webView, nullptr, this, nullptr);
}

void Donator::donate()
{
    if (m_accessKeys.size() < 1)
        return;

    QString accessKey = m_accessKeys.dequeue();
    QString script = QString("document.querySelector('#chaveAcesso').value = '%1';"
                             "document.querySelector('#btnDoarDocumento').click();")
                    .arg(accessKey);
    m_webView->runJavaScript(script);
}

void Donator::loadChanged(const QWebEngineLoadingInfo &info)
{
    if (info.status() != QWebEngineLoadingInfo::LoadSucceededStatus)
        return;

    if (m_loadedHandler != nullptr)
        (this->*m_loadedHandler)();
}

void Donator::prepareForDonations()
{
    m_loadedHandler = &Donator::checkReadyToDonate;
    QObject::connect(m_webView, &QQuickWebEngineView::loadingChanged, this, &Donator::loadChanged);
    m_webView->setUrl(QUrl("https://notaparana.pr.gov.br/nfprweb/DoacaoDocumentoFiscalCadastrar"));
}

void Donator::checkReadyToDonate()
{
        QString script = QString("document.querySelector('#cnpjEntidade').value = '%1';").arg(m_cnpj);
        m_webView->runJavaScript(script);
        m_loadedHandler = &Donator::donate;
        m_webView->runJavaScript("document.querySelector('#btnDoarDocumento').click();");
}
