/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 24, 2023 - 4:54 PM
 */

#ifndef DONATOR_H
#define DONATOR_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebEngineQuick/private/qquickwebengineview_p.h>

class Donator : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickWebEngineView* webView READ webView WRITE setWebView NOTIFY webViewChanged)

public:
    explicit Donator(QObject *parent = nullptr);

    QQuickWebEngineView *webView() const;
    void setWebView(QQuickWebEngineView *newWebView);

public slots:
    void startDonations();

signals:
    void webViewChanged();

private:
    QQuickWebEngineView *m_webView = nullptr;

    void prepareForDonations();
    bool isInDonationPage();
};

#endif // DONATOR_H
