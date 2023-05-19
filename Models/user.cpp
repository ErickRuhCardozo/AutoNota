#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

QString User::fullName() const
{
    return m_fullName;
}

void User::setFullName(const QString &newFullName)
{
    if (m_fullName == newFullName)
        return;

    m_fullName = newFullName;
    emit fullNameChanged();
}

QString User::ssn() const
{
    return m_ssn;
}

void User::setSsn(const QString &newSsn)
{
    if (m_ssn == newSsn)
        return;

    m_ssn = newSsn;
    emit ssnChanged();
}

QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;

    m_password = newPassword;
    emit passwordChanged();
}

bool User::checked() const
{
    return m_checked;
}

void User::setChecked(bool newChecked)
{
    if (m_checked == newChecked)
        return;
    m_checked = newChecked;
    emit checkedChanged();
}
