/****************************************************************************
** Meta object code from reading C++ file 'modelexml.h'
**
** Created: Sat May 24 15:55:44 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Xmlia/modelexml.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelexml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModeleXml[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x05,
      58,   56,   10,   10, 0x05,
      90,   81,   10,   10, 0x05,
     122,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ModeleXml[] = {
    "ModeleXml\0\0n,newName\0"
    "onNodeNameUpdate(QDomNode,QString)\0n\0"
    "onNodeDelete(QDomNode)\0parent,n\0"
    "onNodeInsert(QDomNode,QDomNode)\0"
    "onAboutToBeRemoved(QDomNode)\0"
};

void ModeleXml::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModeleXml *_t = static_cast<ModeleXml *>(_o);
        switch (_id) {
        case 0: _t->onNodeNameUpdate((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->onNodeDelete((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        case 2: _t->onNodeInsert((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QDomNode(*)>(_a[2]))); break;
        case 3: _t->onAboutToBeRemoved((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModeleXml::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModeleXml::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModeleXml,
      qt_meta_data_ModeleXml, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModeleXml::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModeleXml::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModeleXml::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModeleXml))
        return static_cast<void*>(const_cast< ModeleXml*>(this));
    return QObject::qt_metacast(_clname);
}

int ModeleXml::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ModeleXml::onNodeNameUpdate(QDomNode _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModeleXml::onNodeDelete(QDomNode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModeleXml::onNodeInsert(QDomNode _t1, QDomNode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ModeleXml::onAboutToBeRemoved(QDomNode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
