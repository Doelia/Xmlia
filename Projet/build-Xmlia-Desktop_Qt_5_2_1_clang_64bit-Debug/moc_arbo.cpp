/****************************************************************************
** Meta object code from reading C++ file 'arbo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Xmlia/arbo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arbo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Arbo_t {
    QByteArrayData data[8];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Arbo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Arbo_t qt_meta_stringdata_Arbo = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 10),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 6),
QT_MOC_LITERAL(4, 24, 14),
QT_MOC_LITERAL(5, 39, 12),
QT_MOC_LITERAL(6, 52, 13),
QT_MOC_LITERAL(7, 66, 22)
    },
    "Arbo\0updateView\0\0onEdit\0QStandardItem*\0"
    "onRemoveNode\0onRowsRemoved\0"
    "onRowsAboutToBeRemoved\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Arbo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a,
       3,    1,   40,    2, 0x0a,
       5,    0,   43,    2, 0x0a,
       6,    3,   44,    2, 0x0a,
       7,    3,   51,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    2,    2,    2,

       0        // eod
};

void Arbo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Arbo *_t = static_cast<Arbo *>(_o);
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->onEdit((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 2: _t->onRemoveNode(); break;
        case 3: _t->onRowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->onRowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject Arbo::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_Arbo.data,
      qt_meta_data_Arbo,  qt_static_metacall, 0, 0}
};


const QMetaObject *Arbo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Arbo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Arbo.stringdata))
        return static_cast<void*>(const_cast< Arbo*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int Arbo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE