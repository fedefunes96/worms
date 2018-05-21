/****************************************************************************
** Meta object code from reading C++ file 'editorpantalla.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TPWorms/editorpantalla.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorpantalla.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditorPantalla_t {
    QByteArrayData data[15];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorPantalla_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorPantalla_t qt_meta_stringdata_EditorPantalla = {
    {
QT_MOC_LITERAL(0, 0, 14), // "EditorPantalla"
QT_MOC_LITERAL(1, 15, 24), // "on_agregarGusano_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "on_AgregarViga_clicked"
QT_MOC_LITERAL(4, 64, 38), // "on_SelecionarHerramintas_Arma..."
QT_MOC_LITERAL(5, 103, 27), // "on_agregarVigaChica_clicked"
QT_MOC_LITERAL(6, 131, 15), // "mousePressEvent"
QT_MOC_LITERAL(7, 147, 12), // "QMouseEvent*"
QT_MOC_LITERAL(8, 160, 6), // "evento"
QT_MOC_LITERAL(9, 167, 17), // "on_quitar_clicked"
QT_MOC_LITERAL(10, 185, 14), // "on_mas_clicked"
QT_MOC_LITERAL(11, 200, 16), // "on_menos_clicked"
QT_MOC_LITERAL(12, 217, 17), // "on_saveAs_clicked"
QT_MOC_LITERAL(13, 235, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(14, 257, 23) // "on_pushButton_2_clicked"

    },
    "EditorPantalla\0on_agregarGusano_clicked\0"
    "\0on_AgregarViga_clicked\0"
    "on_SelecionarHerramintas_Armas_clicked\0"
    "on_agregarVigaChica_clicked\0mousePressEvent\0"
    "QMouseEvent*\0evento\0on_quitar_clicked\0"
    "on_mas_clicked\0on_menos_clicked\0"
    "on_saveAs_clicked\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorPantalla[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditorPantalla::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorPantalla *_t = static_cast<EditorPantalla *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_agregarGusano_clicked(); break;
        case 1: _t->on_AgregarViga_clicked(); break;
        case 2: _t->on_SelecionarHerramintas_Armas_clicked(); break;
        case 3: _t->on_agregarVigaChica_clicked(); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->on_quitar_clicked(); break;
        case 6: _t->on_mas_clicked(); break;
        case 7: _t->on_menos_clicked(); break;
        case 8: _t->on_saveAs_clicked(); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EditorPantalla::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditorPantalla.data,
      qt_meta_data_EditorPantalla,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EditorPantalla::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorPantalla::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditorPantalla.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int EditorPantalla::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
