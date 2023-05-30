#include "settingsmanager.h"
#include <QSqlQuery>
#include <QSqlError>

SettingsManager::SettingsManager(QObject *parent)
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

void SettingsManager::setCnpj(const QString &newCnpj)
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
    cnpjQuery.exec();
    cnpjQuery.next();
    setCnpj(cnpjQuery.value(0).toString());

    m_db.close();
}

void SettingsManager::saveSettings()
{
    if (!m_db.open()) {
        qCritical() << "Could not open database to save settings";
        return;
    }

    QString sql = QString("UPDATE settings SET value = '%1' WHERE name = 'cnpj'").arg(m_cnpj);
    QSqlQuery query(sql, m_db);

    if (!query.exec()) {
        qWarning() << "Could not save settings";
        qWarning() << query.lastError().text();
    }

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
