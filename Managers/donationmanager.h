/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 24, 2023 - 4:54 PM
 */

#ifndef DONATIONMANAGER_H
#define DONATIONMANAGER_H

#include <QObject>
#include <QQueue>
#include <QQmlEngine>
#include <QWebEngineLoadingInfo>
#include <QtWebEngineQuick/private/qquickwebengineview_p.h>

class DonationManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickWebEngineView* webView READ webView WRITE setWebView NOTIFY webViewChanged)
    Q_PROPERTY(QString cnpj READ cnpj WRITE setCnpj NOTIFY cnpjChanged)
    Q_PROPERTY(int scanned READ scanned NOTIFY scannedChanged)
    Q_PROPERTY(int donated READ donated NOTIFY donatedChanged)
    Q_PROPERTY(int rejected READ rejected NOTIFY rejectedChanged)

public:
    explicit DonationManager(QObject *parent = nullptr);

    QQuickWebEngineView *webView() const;
    void setWebView(QQuickWebEngineView *newWebView);
    QString cnpj() const;
    void setCnpj(const QString &newCnpj);
    int scanned() const;
    int donated() const;
    int rejected() const;
    Q_INVOKABLE void addAccessKey(const QString& accessKey);
    Q_INVOKABLE void disconnect();

public slots:
    void prepareForDonations();

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

signals:
    void webViewChanged();
    void cnpjChanged();
    void scannedChanged();
    void donatedChanged();
    void rejectedChanged();

private:
    QQuickWebEngineView *m_webView = nullptr;
    QString m_cnpj;
    QQueue<QString> m_accessKeys;
    int m_scanned;
    int m_donated;
    int m_rejected;
    bool m_isPrepared;
    void (DonationManager::*m_loadedHandler)();

    void donate();
    void verifyDonation();
    void setScanned(int scanned);
    void setDonated(int donated);
    void setRejected(int rejected);
};

#endif // DONATIONMANAGER_H
