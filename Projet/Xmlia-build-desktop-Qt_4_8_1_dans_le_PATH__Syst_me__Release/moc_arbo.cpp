/****************************************************************************
** Meta object code from reading C++ file 'arbo.h'
**
** Created: Thu Apr 24 15:57:55 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Xmlia/arbo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arbo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Arbo[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      19,    5,    5,    5, 0x0a,
      42,    5,    5,    5, 0x0a,
      60,   57,    5,    5, 0x0a,
      95,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Arbo[] = {
    "Arbo\0\0updateView()\0onEdit(QStandardItem*)\0"
    "onRemoveNode()\0,,\0onRowsRemoved(QModelIndex,int,int)\0"
    "onNodeDelete(QDomNode)\0"
};

void Arbo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Arbo *_t = static_cast<Arbo *>(_o);
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->onEdit((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 2: _t->onRemoveNode(); break;
        case 3: _t->onRowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->onNodeDelete((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Arbo::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Arbo::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_Arbo,
      qt_meta_data_Arbo, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Arbo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Arbo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Arbo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Arbo))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
