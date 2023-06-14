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
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn CONSTANT)
    Q_PROPERTY(bool hasLoginErrors READ hasLoginErrors NOTIFY hasLoginErrorsChanged)

public:
    explicit LoginManager(QObject* parent = nullptr);
    bool isLoggedIn() const;

    QQuickWebEngineView* webView() const;
    void setWebView(QQuickWebEngineView* newWebView);

    Q_INVOKABLE void login(const QString& user, const QString& ssn, const QString& password);
    Q_INVOKABLE void logout();

    bool hasLoginErrors() const;

    QString status() const;
    void setStatus(const QString& newStatus);

signals:
    void webViewChanged();
    void successfullyLoggedIn();
    void hasLoginErrorsChanged();
    void loginRequested();
    void statusChanged();

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

private:
    static const QString AUTH_URL;

    QQuickWebEngineView* m_webView = nullptr;
    QString m_status;
    QString m_currentSsn;
    QString m_currentPassword;
    QJSEngine m_engine;
    bool m_isLoggedIn;
    bool m_hasLoginErrors;
    void (LoginManager::*m_loadedHandler)();

    void fillLoginInfo();
    void checkAfterLoginAttempt();
    void setLoginError(bool error);
};

#endif // LOGINMANAGER_H
