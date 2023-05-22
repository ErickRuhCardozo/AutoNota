#ifndef USER_H
#define USER_H

#include <QObject>
#include <QQmlEngine>

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString ssn READ ssn WRITE setSsn NOTIFY ssnChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    explicit User(QObject *parent = nullptr);

    QString fullName() const;
    void setFullName(const QString &newFullName);

    QString ssn() const;
    void setSsn(const QString &newSsn);

    QString password() const;
    void setPassword(const QString &newPassword);

signals:
    void fullNameChanged();
    void ssnChanged();
    void passwordChanged();

private:
    QString m_fullName;
    QString m_ssn;
    QString m_password;
};

#endif // USER_H
