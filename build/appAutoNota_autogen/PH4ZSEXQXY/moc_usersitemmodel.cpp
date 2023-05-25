/****************************************************************************
** Meta object code from reading C++ file 'usersitemmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ItemModels/usersitemmodel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usersitemmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSUsersItemModelENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSUsersItemModelENDCLASS = QtMocHelpers::stringData(
    "UsersItemModel",
    "QML.Element",
    "auto",
    "addUser",
    "",
    "name",
    "ssn",
    "password",
    "loadUsers",
    "saveUsers",
    "createUsersFile",
    "UserRole",
    "NameRole",
    "SsnRole",
    "PasswordRole",
    "ObjectRole"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSUsersItemModelENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[8];
    char stringdata4[1];
    char stringdata5[5];
    char stringdata6[4];
    char stringdata7[9];
    char stringdata8[10];
    char stringdata9[10];
    char stringdata10[16];
    char stringdata11[9];
    char stringdata12[9];
    char stringdata13[8];
    char stringdata14[13];
    char stringdata15[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSUsersItemModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSUsersItemModelENDCLASS_t qt_meta_stringdata_CLASSUsersItemModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "UsersItemModel"
        QT_MOC_LITERAL(15, 11),  // "QML.Element"
        QT_MOC_LITERAL(27, 4),  // "auto"
        QT_MOC_LITERAL(32, 7),  // "addUser"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 4),  // "name"
        QT_MOC_LITERAL(46, 3),  // "ssn"
        QT_MOC_LITERAL(50, 8),  // "password"
        QT_MOC_LITERAL(59, 9),  // "loadUsers"
        QT_MOC_LITERAL(69, 9),  // "saveUsers"
        QT_MOC_LITERAL(79, 15),  // "createUsersFile"
        QT_MOC_LITERAL(95, 8),  // "UserRole"
        QT_MOC_LITERAL(104, 8),  // "NameRole"
        QT_MOC_LITERAL(113, 7),  // "SsnRole"
        QT_MOC_LITERAL(121, 12),  // "PasswordRole"
        QT_MOC_LITERAL(134, 10)   // "ObjectRole"
    },
    "UsersItemModel",
    "QML.Element",
    "auto",
    "addUser",
    "",
    "name",
    "ssn",
    "password",
    "loadUsers",
    "saveUsers",
    "createUsersFile",
    "UserRole",
    "NameRole",
    "SsnRole",
    "PasswordRole",
    "ObjectRole"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSUsersItemModelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       1,   14, // classinfo
       4,   16, // methods
       0,    0, // properties
       1,   50, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    3,   40,    4, 0x02,    1 /* Public */,
       8,    0,   47,    4, 0x02,    5 /* Public */,
       9,    0,   48,    4, 0x02,    6 /* Public */,
      10,    0,   49,    4, 0x02,    7 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      11,   11, 0x0,    4,   55,

 // enum data: key, value
      12, uint(UsersItemModel::NameRole),
      13, uint(UsersItemModel::SsnRole),
      14, uint(UsersItemModel::PasswordRole),
      15, uint(UsersItemModel::ObjectRole),

       0        // eod
};

Q_CONSTINIT const QMetaObject UsersItemModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSUsersItemModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSUsersItemModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // Q_OBJECT / Q_GADGET
        UsersItemModel,
        // method 'addUser'
        void,
        const QString &,
        const QString &,
        const QString &,
        // method 'loadUsers'
        void,
        // method 'saveUsers'
        void,
        // method 'createUsersFile'
        void
    >,
    nullptr
} };

void UsersItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UsersItemModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 1: _t->loadUsers(); break;
        case 2: _t->saveUsers(); break;
        case 3: _t->createUsersFile(); break;
        default: ;
        }
    }
}

const QMetaObject *UsersItemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UsersItemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSUsersItemModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int UsersItemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
