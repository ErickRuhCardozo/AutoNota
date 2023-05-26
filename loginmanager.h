/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 23, 2023 - 2:41 PM
 */

#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QWebEngineLoadingInfo>
#include <QtWebEngineQuick/private/qquickwebengineview_p.h>

class LoginManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickWebEngineView* webView READ webView WRITE setWebView NOTIFY webViewChanged)
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn CONSTANT)

public:
    explicit LoginManager(QObject *parent = nullptr);
    bool isLoggedIn() const;

    QQuickWebEngineView *webView() const;
    void setWebView(QQuickWebEngineView *newWebView);

    Q_INVOKABLE void login(QString ssn, QString password);
    Q_INVOKABLE void logout();

signals:
    void webViewChanged();
    void successfullyLoggedIn();

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

private:
    static const QString AUTH_URL;

    QQuickWebEngineView *m_webView = nullptr;
    bool m_isLoggedIn;
    bool m_skipCheckAfterLogin;
    QString m_currentSsn;
    QString m_currentPassword;
    void (LoginManager::*m_loadedHandler)();

    void fillLoginInfo();
    void checkAfterLogin();
    void checkFinalizedSession();
};

#endif // LOGINMANAGER_H
