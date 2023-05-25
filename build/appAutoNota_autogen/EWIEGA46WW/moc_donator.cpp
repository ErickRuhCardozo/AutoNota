/****************************************************************************
** Meta object code from reading C++ file 'donator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../donator.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'donator.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSDonatorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSDonatorENDCLASS = QtMocHelpers::stringData(
    "Donator",
    "QML.Element",
    "auto",
    "webViewChanged",
    "",
    "cnpjChanged",
    "prepareForDonations",
    "loadChanged",
    "QWebEngineLoadingInfo",
    "info",
    "addAccessKey",
    "accessKey",
    "webView",
    "QQuickWebEngineView*",
    "cnpj"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSDonatorENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[8];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[15];
    char stringdata4[1];
    char stringdata5[12];
    char stringdata6[20];
    char stringdata7[12];
    char stringdata8[22];
    char stringdata9[5];
    char stringdata10[13];
    char stringdata11[10];
    char stringdata12[8];
    char stringdata13[21];
    char stringdata14[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSDonatorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSDonatorENDCLASS_t qt_meta_stringdata_CLASSDonatorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "Donator"
        QT_MOC_LITERAL(8, 11),  // "QML.Element"
        QT_MOC_LITERAL(20, 4),  // "auto"
        QT_MOC_LITERAL(25, 14),  // "webViewChanged"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 11),  // "cnpjChanged"
        QT_MOC_LITERAL(53, 19),  // "prepareForDonations"
        QT_MOC_LITERAL(73, 11),  // "loadChanged"
        QT_MOC_LITERAL(85, 21),  // "QWebEngineLoadingInfo"
        QT_MOC_LITERAL(107, 4),  // "info"
        QT_MOC_LITERAL(112, 12),  // "addAccessKey"
        QT_MOC_LITERAL(125, 9),  // "accessKey"
        QT_MOC_LITERAL(135, 7),  // "webView"
        QT_MOC_LITERAL(143, 20),  // "QQuickWebEngineView*"
        QT_MOC_LITERAL(164, 4)   // "cnpj"
    },
    "Donator",
    "QML.Element",
    "auto",
    "webViewChanged",
    "",
    "cnpjChanged",
    "prepareForDonations",
    "loadChanged",
    "QWebEngineLoadingInfo",
    "info",
    "addAccessKey",
    "accessKey",
    "webView",
    "QQuickWebEngineView*",
    "cnpj"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDonatorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       1,   14, // classinfo
       5,   16, // methods
       2,   55, // properties
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
       6,    0,   48,    4, 0x0a,    5 /* Public */,
       7,    1,   49,    4, 0x08,    6 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   52,    4, 0x02,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   11,

 // properties: name, type, flags
      12, 0x80000000 | 13, 0x0001510b, uint(0), 0,
      14, QMetaType::QString, 0x00015103, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject Donator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSDonatorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDonatorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'webView'
        QQuickWebEngineView*,
        // property 'cnpj'
        QString,
        // Q_OBJECT / Q_GADGET
        Donator,
        // method 'webViewChanged'
        void,
        // method 'cnpjChanged'
        void,
        // method 'prepareForDonations'
        void,
        // method 'loadChanged'
        void,
        const QWebEngineLoadingInfo &,
        // method 'addAccessKey'
        void,
        const QString &
    >,
    nullptr
} };

void Donator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Donator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->webViewChanged(); break;
        case 1: _t->cnpjChanged(); break;
        case 2: _t->prepareForDonations(); break;
        case 3: _t->loadChanged((*reinterpret_cast< std::add_pointer_t<QWebEngineLoadingInfo>>(_a[1]))); break;
        case 4: _t->addAccessKey((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Donator::*)();
            if (_t _q_method = &Donator::webViewChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Donator::*)();
            if (_t _q_method = &Donator::cnpjChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
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
        auto *_t = static_cast<Donator *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QQuickWebEngineView**>(_v) = _t->webView(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->cnpj(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Donator *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWebView(*reinterpret_cast< QQuickWebEngineView**>(_v)); break;
        case 1: _t->setCnpj(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *Donator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Donator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDonatorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Donator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Donator::webViewChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Donator::cnpjChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
