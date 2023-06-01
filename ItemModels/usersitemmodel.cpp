#include "usersitemmodel.h"
#include <QSqlError>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>

const QString UsersItemModel::FILENAME = "users.dat";

UsersItemModel::UsersItemModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_db = QSqlDatabase::database();
    loadUsers();
}

UsersItemModel::~UsersItemModel()
{
    saveUsers();
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

int UsersItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_users.size();
}

int UsersItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant UsersItemModel::data(const QModelIndex &index, int role) const
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

bool UsersItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

Qt::ItemFlags UsersItemModel::flags(const QModelIndex &index) const
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

bool UsersItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_db.open();
    const User* user = m_users.at(row);
    QSqlQuery query(QString("DELETE FROM users WHERE id = %1").arg(QString::number(user->id())));
    query.exec();
    m_users.remove(row);
    endRemoveRows();
    m_db.close();
    return true;
}

void UsersItemModel::addUser(const QString &name, const QString &ssn, const QString &password)
{
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

void UsersItemModel::saveUsers()
{
    if (m_unsavedUsers.size() == 0)
        return;

    if (!m_db.open()) {
        qCritical() << "Could not open database to save users";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (name, ssn, password) VALUES (?, ?, ?)");

    for (const User* user : qAsConst(m_unsavedUsers)) {
        query.bindValue(0, user->fullName());
        query.bindValue(1, user->ssn());
        query.bindValue(2, user->password());

        if (!query.exec()) {
            qCritical() << "Error saving user: " << query.lastError().text();
        }
    }

    m_db.close();
}

const User *UsersItemModel::getUser(int id)
{
    for (const User* user : qAsConst(m_users)) {
        if (user->id() == id) {
            return user;
        }
    }

    return nullptr;
}
