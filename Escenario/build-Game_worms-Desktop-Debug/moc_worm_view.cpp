/****************************************************************************
** Meta object code from reading C++ file 'worm_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Game_worms/worm_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worm_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Worm_View_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worm_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worm_View_t qt_meta_stringdata_Worm_View = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Worm_View"
QT_MOC_LITERAL(1, 10, 15), // "nextFrame2_Left"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "nextFrame2_Right"
QT_MOC_LITERAL(4, 44, 17), // "nextFrame2_UpLeft"
QT_MOC_LITERAL(5, 62, 19) // "nextFrame2_UpLeft30"

    },
    "Worm_View\0nextFrame2_Left\0\0nextFrame2_Right\0"
    "nextFrame2_UpLeft\0nextFrame2_UpLeft30"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worm_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Worm_View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worm_View *_t = static_cast<Worm_View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextFrame2_Left(); break;
        case 1: _t->nextFrame2_Right(); break;
        case 2: _t->nextFrame2_UpLeft(); break;
        case 3: _t->nextFrame2_UpLeft30(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Worm_View::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worm_View.data,
      qt_meta_data_Worm_View,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Worm_View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worm_View::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Worm_View.stringdata0))
        return static_cast<void*>(const_cast< Worm_View*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Worm_View*>(this));
    return QObject::qt_metacast(_clname);
}

int Worm_View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE