#include "usersitemmodel.h"
#include <QSqlError>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>

UsersItemModel::UsersItemModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_db = QSqlDatabase::database();
    loadUsers();
}

QVariant UsersItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (section) {
        case 0:
            return "Nome";

        case 1:
            return "CPF";

        default:
            return "";
    }
}

int UsersItemModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_users.size();
}

int UsersItemModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant UsersItemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const User* user = m_users.at(index.row());

    switch (role) {
        case IdRole:
            return user->id();

        case NameRole:
            return user->fullName();

        case SsnRole:
            return user->ssn();

        case PasswordRole:
            return user->password();

        case ObjectRole:
            return QVariant::fromValue(user);
    }

    return QVariant();
}

bool UsersItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value) {
        User* user = m_users.at(index.row());

        switch (role) {
            case NameRole:
                user->setFullName(value.toString());
                break;

            case SsnRole:
                user->setSsn(value.toString());
                break;

            case PasswordRole:
                user->setPassword(value.toString());
                break;
        }

        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

Qt::ItemFlags UsersItemModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> UsersItemModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { NameRole, "name" },
        { SsnRole, "ssn" },
        { PasswordRole, "password" },
        { ObjectRole, "userObject" },
    };
}

bool UsersItemModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (!m_db.open()) {
        qCritical() << "Could not open db to remove users";
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);
    const User* user = m_users.at(row);
    QSqlQuery query(QString("DELETE FROM users WHERE id = %1").arg(QString::number(user->id())));
    query.exec();
    m_users.remove(row);
    m_db.close();
    endRemoveRows();
    return true;
}

void UsersItemModel::addUser(const QString& name, const QString& ssn, const QString& password)
{
    if (!m_db.open()) {
        qCritical() << "Could not open database to add user";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (name, ssn, password) VALUES (?, ?, ?)");
    query.bindValue(0, name);
    query.bindValue(1, ssn);
    query.bindValue(2, password);
    bool success = query.exec();

    if (!success) {
        QString error = processSqlError(query.lastError().text());
        setError(error);
    } else {
        setError("");
        const int size = m_users.size();
        beginInsertRows(QModelIndex(), size, size);
        User* user = new User(this);
        user->setFullName(name);
        user->setSsn(ssn);
        user->setPassword(password);
        m_users.append(user);
        m_unsavedUsers.append(user);
        endInsertRows();
    }

    m_db.close();
}

void UsersItemModel::loadUsers()
{
    if (!m_db.open()) {
        qCritical() << "Could not open database to load users";
        return;
    }

    QSqlQuery query("SELECT id, name, ssn, password FROM users", m_db);
    query.exec();

    while (query.next()) {
        User* user = new User();
        user->setId(query.value(0).toInt());
        user->setFullName(query.value(1).toString());
        user->setSsn(query.value(2).toString());
        user->setPassword(query.value(3).toString());
        m_users.append(user);
    }

    m_db.close();
}

const User* UsersItemModel::getUser(int id)
{
    for (const User* user : qAsConst(m_users)) {
        if (user->id() == id) {
            return user;
        }
    }

    return nullptr;
}

QString UsersItemModel::error() const
{
    return m_error;
}

void UsersItemModel::setError(const QString& newerror)
{
    if (m_error == newerror)
        return;

    m_error = newerror;
    emit errorChanged();
    emit errorOcurred();
}

QString UsersItemModel::processSqlError(const QString& errorText)
{
    if (errorText.contains("UNIQUE")) {
        if (errorText.contains("users.name")) {
            return "Nome já cadastrado. Escolha outro.";
        } else if (errorText.contains("users.ssn")) {
            return "CPF Já cadastrsado. Escolha outro.";
        }
    }

    return QString("Erro Desconhecido: %1").arg(errorText);
}
