#include "settingsmanager.h"
#include <QSqlQuery>
#include <QSqlError>

SettingsManager::SettingsManager(QObject* parent)
    : QObject{parent},
    m_defaultUser{-1}
{
    m_db = QSqlDatabase::database();
    loadSettings();
}

SettingsManager::~SettingsManager()
{
    saveSettings();
}

QString SettingsManager::cnpj() const
{
    return m_cnpj;
}

void SettingsManager::setCnpj(const QString& newCnpj)
{
    if (m_cnpj == newCnpj)
        return;
    m_cnpj = newCnpj;
    emit cnpjChanged();
}

void SettingsManager::loadSettings()
{
    if (!m_db.open()) {
        qCritical() << "Could not open database to load settings";
        return;
    }

    QSqlQuery cnpjQuery("SELECT value FROM settings WHERE name = 'cnpj'", m_db);
    QSqlQuery userQuery("SELECT value FROM settings WHERE name = 'default_user'", m_db);
    cnpjQuery.exec();
    userQuery.exec();
    cnpjQuery.next();
    userQuery.next();
    int defaultUserId = userQuery.value(0).toInt();
    setCnpj(cnpjQuery.value(0).toString());
    setDefaultUser(defaultUserId == 0 ? -1 : defaultUserId);
    m_db.close();
}

void SettingsManager::saveSettings()
{
    if (!m_db.open()) {
        qCritical() << "Could not open database to save settings";
        return;
    }

    QString cnpjSql = QString("UPDATE settings SET value = '%1' WHERE name = 'cnpj'").arg(m_cnpj);
    QString defaultUserSql = QString("UPDATE settings SET value = '%1' WHERE name = 'default_user'").arg(m_defaultUser);
    QSqlQuery cnpjQuery(cnpjSql, m_db);
    QSqlQuery userQuery(defaultUserSql, m_db);
    cnpjQuery.exec();
    userQuery.exec();
    m_db.close();
}

int SettingsManager::defaultUser() const
{
    return m_defaultUser;
}

void SettingsManager::setDefaultUser(int newDefaultUser)
{
    if (m_defaultUser == newDefaultUser)
        return;
    m_defaultUser = newDefaultUser;
    emit defaultUserChanged();
}
