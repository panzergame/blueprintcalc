/****************************************************************************
** Meta object code from reading C++ file 'selector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/selector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Selector_t {
    QByteArrayData data[7];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Selector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Selector_t qt_meta_stringdata_Selector = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Selector"
QT_MOC_LITERAL(1, 9, 10), // "pointAdded"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 19), // "ImageViewType::Type"
QT_MOC_LITERAL(4, 41, 8), // "viewType"
QT_MOC_LITERAL(5, 50, 17), // "Alignment::Point*"
QT_MOC_LITERAL(6, 68, 5) // "point"

    },
    "Selector\0pointAdded\0\0ImageViewType::Type\0"
    "viewType\0Alignment::Point*\0point"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Selector[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void Selector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Selector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pointAdded((*reinterpret_cast< ImageViewType::Type(*)>(_a[1])),(*reinterpret_cast< Alignment::Point*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Selector::*)(ImageViewType::Type , Alignment::Point * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Selector::pointAdded)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Selector::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Selector.data,
    qt_meta_data_Selector,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Selector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Selector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Selector.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Singleton<Selector>"))
        return static_cast< Singleton<Selector>*>(this);
    return QObject::qt_metacast(_clname);
}

int Selector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Selector::pointAdded(ImageViewType::Type _t1, Alignment::Point * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
