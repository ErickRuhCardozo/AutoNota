/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 17, 2023 - 3:33 PM
 */

#ifndef USERSITEMMODEL_H
#define USERSITEMMODEL_H

#include "qqmlintegration.h"
#include "../Models/user.h"
#include <QAbstractTableModel>
#include <QSqlDatabase>

class UsersItemModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    enum UserRole {
        IdRole = Qt::UserRole + 1,
        NameRole,
        SsnRole,
        PasswordRole,
        ObjectRole
    };
    Q_ENUM(UserRole)

    explicit UsersItemModel(QObject* parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    Q_INVOKABLE void addUser(const QString& name, const QString& ssn, const QString& password);
    Q_INVOKABLE const User* getUser(int id);

    QString error() const;

signals:
    void errorOcurred();
    void errorChanged();

private:
    QList<User*> m_users;
    QList<User*> m_unsavedUsers;
    QSqlDatabase m_db;
    QString m_error;

    void loadUsers();
    void setError(const QString& newerror);
    QString processSqlError(const QString& errorText);
};

#endif // USERSITEMMODEL_H
