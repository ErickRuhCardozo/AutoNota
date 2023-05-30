/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 17, 2023 - 2:15 PM
 */
#ifndef USER_H
#define USER_H

#include <QObject>
#include <QQmlEngine>

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString ssn READ ssn WRITE setSsn NOTIFY ssnChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    explicit User(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString fullName() const;
    void setFullName(const QString &newFullName);

    QString ssn() const;
    void setSsn(const QString &newSsn);

    QString password() const;
    void setPassword(const QString &newPassword);

signals:
    void idChanged();
    void fullNameChanged();
    void ssnChanged();
    void passwordChanged();    

private:
    int m_id;
    QString m_fullName;
    QString m_ssn;
    QString m_password;
};

#endif // USER_H
