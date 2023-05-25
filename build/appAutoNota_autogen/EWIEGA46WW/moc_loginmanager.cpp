/****************************************************************************
** Meta object code from reading C++ file 'loginmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../loginmanager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginmanager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSLoginManagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSLoginManagerENDCLASS = QtMocHelpers::stringData(
    "LoginManager",
    "QML.Element",
    "auto",
    "webViewChanged",
    "",
    "successfullyLoggedIn",
    "loadChanged",
    "QWebEngineLoadingInfo",
    "info",
    "login",
    "ssn",
    "password",
    "logout",
    "webView",
    "QQuickWebEngineView*",
    "isLoggedIn"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSLoginManagerENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[15];
    char stringdata4[1];
    char stringdata5[21];
    char stringdata6[12];
    char stringdata7[22];
    char stringdata8[5];
    char stringdata9[6];
    char stringdata10[4];
    char stringdata11[9];
    char stringdata12[7];
    char stringdata13[8];
    char stringdata14[21];
    char stringdata15[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSLoginManagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSLoginManagerENDCLASS_t qt_meta_stringdata_CLASSLoginManagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "LoginManager"
        QT_MOC_LITERAL(13, 11),  // "QML.Element"
        QT_MOC_LITERAL(25, 4),  // "auto"
        QT_MOC_LITERAL(30, 14),  // "webViewChanged"
        QT_MOC_LITERAL(45, 0),  // ""
        QT_MOC_LITERAL(46, 20),  // "successfullyLoggedIn"
        QT_MOC_LITERAL(67, 11),  // "loadChanged"
        QT_MOC_LITERAL(79, 21),  // "QWebEngineLoadingInfo"
        QT_MOC_LITERAL(101, 4),  // "info"
        QT_MOC_LITERAL(106, 5),  // "login"
        QT_MOC_LITERAL(112, 3),  // "ssn"
        QT_MOC_LITERAL(116, 8),  // "password"
        QT_MOC_LITERAL(125, 6),  // "logout"
        QT_MOC_LITERAL(132, 7),  // "webView"
        QT_MOC_LITERAL(140, 20),  // "QQuickWebEngineView*"
        QT_MOC_LITERAL(161, 10)   // "isLoggedIn"
    },
    "LoginManager",
    "QML.Element",
    "auto",
    "webViewChanged",
    "",
    "successfullyLoggedIn",
    "loadChanged",
    "QWebEngineLoadingInfo",
    "info",
    "login",
    "ssn",
    "password",
    "logout",
    "webView",
    "QQuickWebEngineView*",
    "isLoggedIn"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLoginManagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       1,   14, // classinfo
       5,   16, // methods
       2,   57, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   46,    4, 0x06,    3 /* Public */,
       5,    0,   47,    4, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   48,    4, 0x08,    5 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,   51,    4, 0x02,    7 /* Public */,
      12,    0,   56,    4, 0x02,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,

 // properties: name, type, flags
      13, 0x80000000 | 14, 0x0001510b, uint(0), 0,
      15, QMetaType::Bool, 0x00015401, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject LoginManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSLoginManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLoginManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'webView'
        QQuickWebEngineView*,
        // property 'isLoggedIn'
        bool,
        // Q_OBJECT / Q_GADGET
        LoginManager,
        // method 'webViewChanged'
        void,
        // method 'successfullyLoggedIn'
        void,
        // method 'loadChanged'
        void,
        const QWebEngineLoadingInfo &,
        // method 'login'
        void,
        QString,
        QString,
        // method 'logout'
        void
    >,
    nullptr
} };

void LoginManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->webViewChanged(); break;
        case 1: _t->successfullyLoggedIn(); break;
        case 2: _t->loadChanged((*reinterpret_cast< std::add_pointer_t<QWebEngineLoadingInfo>>(_a[1]))); break;
        case 3: _t->login((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->logout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginManager::*)();
            if (_t _q_method = &LoginManager::webViewChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginManager::*)();
            if (_t _q_method = &LoginManager::successfullyLoggedIn; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQuickWebEngineView* >(); break;
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LoginManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QQuickWebEngineView**>(_v) = _t->webView(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isLoggedIn(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LoginManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWebView(*reinterpret_cast< QQuickWebEngineView**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *LoginManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLoginManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LoginManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoginManager::webViewChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginManager::successfullyLoggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
