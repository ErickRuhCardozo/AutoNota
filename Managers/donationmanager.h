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

public:
    explicit DonationManager(QObject *parent = nullptr);

    QQuickWebEngineView *webView() const;
    void setWebView(QQuickWebEngineView *newWebView);

    QString cnpj() const;
    void setCnpj(const QString &newCnpj);

    Q_INVOKABLE void addAccessKey(const QString& accessKey);
    Q_INVOKABLE void disconnect();

public slots:
    void prepareForDonations();

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

signals:
    void webViewChanged();
    void cnpjChanged();

private:
    QQuickWebEngineView *m_webView = nullptr;
    QString m_cnpj;
    QQueue<QString> m_accessKeys;
    bool m_isPrepared;
    void (DonationManager::*m_loadedHandler)();

    void donate();
};

#endif // DONATIONMANAGER_H
