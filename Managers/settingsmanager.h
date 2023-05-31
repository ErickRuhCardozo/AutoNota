#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QSqlDatabase>

class SettingsManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int defaultUser READ defaultUser WRITE setDefaultUser NOTIFY defaultUserChanged)
    Q_PROPERTY(QString cnpj READ cnpj WRITE setCnpj NOTIFY cnpjChanged)

public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager();

    QString cnpj() const;
    void setCnpj(const QString &newCnpj);
    Q_INVOKABLE void loadSettings();
    Q_INVOKABLE void saveSettings();

    int defaultUser() const;
    void setDefaultUser(int newDefaultUser);

signals:
    void cnpjChanged();
    void defaultUserChanged();

private:
    QString m_cnpj;
    QSqlDatabase m_db;
    int m_defaultUser;
};

#endif // SETTINGSMANAGER_H
