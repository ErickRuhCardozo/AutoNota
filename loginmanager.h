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
    Q_PROPERTY(bool hasLoginErrors READ hasLoginErrors NOTIFY hasLoginErrorsChanged)

public:
    explicit LoginManager(QObject *parent = nullptr);
    bool isLoggedIn() const;

    QQuickWebEngineView *webView() const;
    void setWebView(QQuickWebEngineView *newWebView);

    Q_INVOKABLE void login(QString ssn, QString password);
    Q_INVOKABLE void logout();

    bool hasLoginErrors() const;

signals:
    void webViewChanged();
    void successfullyLoggedIn();
    void hasLoginErrorsChanged();

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

private:
    static const QString AUTH_URL;

    QQuickWebEngineView *m_webView = nullptr;
    QJSEngine m_engine;
    bool m_isLoggedIn;
    bool m_skipCheckAfterLogin;
    bool m_hasLoginErrors;
    QString m_currentSsn;
    QString m_currentPassword;
    void (LoginManager::*m_loadedHandler)();

    void fillLoginInfo();
    void checkAfterLogin();
    void checkFinalizedSession();
    void setLoginError(bool error);
};

#endif // LOGINMANAGER_H
