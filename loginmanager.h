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

private slots:
    void loadChanged(const QWebEngineLoadingInfo& info);

signals:
    void webViewChanged();

private:
    static const QString AUTH_URL;

    QQuickWebEngineView *m_webView = nullptr;
    bool m_isLoggedIn;
    QString m_currentSsn;
    QString m_currentPassword;
    void (LoginManager::*m_loadedHandler)();

    void fillLoginInfo();
    void checkForInitializedSession();
};

#endif // LOGINMANAGER_H
