/****************************************************************************
** Meta object code from reading C++ file 'editorseleccionarmasherramientas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TPWorms/editorseleccionarmasherramientas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorseleccionarmasherramientas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_editorSeleccionArmasHerramientas_t {
    QByteArrayData data[12];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_editorSeleccionArmasHerramientas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_editorSeleccionArmasHerramientas_t qt_meta_stringdata_editorSeleccionArmasHerramientas = {
    {
QT_MOC_LITERAL(0, 0, 32), // "editorSeleccionArmasHerramientas"
QT_MOC_LITERAL(1, 33, 18), // "on_bazooka_clicked"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 18), // "on_Mortero_clicked"
QT_MOC_LITERAL(4, 72, 19), // "on_GranadaV_clicked"
QT_MOC_LITERAL(5, 92, 19), // "on_GranadaR_clicked"
QT_MOC_LITERAL(6, 112, 17), // "on_Banana_clicked"
QT_MOC_LITERAL(7, 130, 19), // "on_GranadaS_clicked"
QT_MOC_LITERAL(8, 150, 19), // "on_Dinamita_clicked"
QT_MOC_LITERAL(9, 170, 15), // "on_Bate_clicked"
QT_MOC_LITERAL(10, 186, 16), // "on_Aereo_clicked"
QT_MOC_LITERAL(11, 203, 28) // "on_Teletransportador_clicked"

    },
    "editorSeleccionArmasHerramientas\0"
    "on_bazooka_clicked\0\0on_Mortero_clicked\0"
    "on_GranadaV_clicked\0on_GranadaR_clicked\0"
    "on_Banana_clicked\0on_GranadaS_clicked\0"
    "on_Dinamita_clicked\0on_Bate_clicked\0"
    "on_Aereo_clicked\0on_Teletransportador_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_editorSeleccionArmasHerramientas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void editorSeleccionArmasHerramientas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        editorSeleccionArmasHerramientas *_t = static_cast<editorSeleccionArmasHerramientas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_bazooka_clicked(); break;
        case 1: _t->on_Mortero_clicked(); break;
        case 2: _t->on_GranadaV_clicked(); break;
        case 3: _t->on_GranadaR_clicked(); break;
        case 4: _t->on_Banana_clicked(); break;
        case 5: _t->on_GranadaS_clicked(); break;
        case 6: _t->on_Dinamita_clicked(); break;
        case 7: _t->on_Bate_clicked(); break;
        case 8: _t->on_Aereo_clicked(); break;
        case 9: _t->on_Teletransportador_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject editorSeleccionArmasHerramientas::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_editorSeleccionArmasHerramientas.data,
      qt_meta_data_editorSeleccionArmasHerramientas,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *editorSeleccionArmasHerramientas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *editorSeleccionArmasHerramientas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_editorSeleccionArmasHerramientas.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int editorSeleccionArmasHerramientas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
