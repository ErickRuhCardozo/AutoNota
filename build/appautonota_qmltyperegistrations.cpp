/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <donator.h>
#include <loginmanager.h>
#include <user.h>
#include <usersitemmodel.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_AutoNota()
{
    qmlRegisterTypesAndRevisions<Donator>("AutoNota", 1);
    qmlRegisterTypesAndRevisions<LoginManager>("AutoNota", 1);
    QMetaType::fromType<QAbstractTableModel *>().id();
    qmlRegisterTypesAndRevisions<User>("AutoNota", 1);
    qmlRegisterTypesAndRevisions<UsersItemModel>("AutoNota", 1);
    qmlRegisterAnonymousType<QAbstractItemModel, 254>("AutoNota", 1);
    qmlRegisterModule("AutoNota", 1, 0);
}

static const QQmlModuleRegistration registration("AutoNota", qml_register_types_AutoNota);
