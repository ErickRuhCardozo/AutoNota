#include "usersitemmodel.h"
#include <QFile>
#include <QDebug>

const QString UsersItemModel::FILENAME = "users.dat";

UsersItemModel::UsersItemModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    if (!QFile::exists(FILENAME)) {
        createUsersFile();
    }

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

        case 2:
            return "Senha";

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

    return 3;
}

QVariant UsersItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const User* user = m_users.at(index.row());

    switch (role) {
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
        { NameRole, "name" },
        { SsnRole, "ssn" },
        { PasswordRole, "password" },
        { ObjectRole, "userObject" }
    };
}

bool UsersItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_users.remove(row);
    endRemoveRows();
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
    endInsertRows();
}

void UsersItemModel::loadUsers()
{
    QFile file(FILENAME);

    if (!file.open(QFile::Text | QFile::ReadOnly)) {
        qCritical("Could not open %s to read", qUtf8Printable(FILENAME));
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList values = line.split(',');

        if (values.size() < 3)
                continue;

        User* user = new User(this);
        user->setFullName(values[0]);
        user->setSsn(values[1]);
        values[2].chop(1);
        user->setPassword(values[2]);
        m_users.append(user);
    }
}

void UsersItemModel::saveUsers()
{
    QFile file(FILENAME);

    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        qCritical("Could not open %s to write", qUtf8Printable(FILENAME));
        return;
    }

    QStringList lines;

    for (const User* user : m_users) {
        QString line = QString("%1,%2,%3\n").arg(user->fullName(), user->ssn(), user->password());
        lines.append(line);
    }

    file.write(lines.join("\n").toUtf8());
    file.close();
}

void UsersItemModel::createUsersFile()
{
    QFile file(FILENAME);

    if (!file.open(QFile::Text | QFile::ReadWrite)) {
        qCritical("Could not create users file");
    }

    file.close();
}
