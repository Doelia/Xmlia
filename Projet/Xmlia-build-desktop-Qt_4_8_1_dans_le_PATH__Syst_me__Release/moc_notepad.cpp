/****************************************************************************
** Meta object code from reading C++ file 'notepad.h'
**
** Created: Mon Apr 28 09:59:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Xmlia/notepad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomTabWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      33,   16,   16,   16, 0x08,
      44,   16,   16,   16, 0x08,
      55,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CustomTabWidget[] = {
    "CustomTabWidget\0\0onShiftTabHit()\0"
    "onTabHit()\0onToggle()\0onTabChanged()\0"
};

void CustomTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomTabWidget *_t = static_cast<CustomTabWidget *>(_o);
        switch (_id) {
        case 0: _t->onShiftTabHit(); break;
        case 1: _t->onTabHit(); break;
        case 2: _t->onToggle(); break;
        case 3: _t->onTabChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CustomTabWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_CustomTabWidget,
      qt_meta_data_CustomTabWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomTabWidget))
        return static_cast<void*>(const_cast< CustomTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int CustomTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_NotePad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      22,   18,    8,    8, 0x05,
      44,   42,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   42,    8,    8, 0x0a,
      99,    8,    8,    8, 0x0a,
     131,  122,    8,    8, 0x0a,
     163,    8,    8,    8, 0x0a,
     192,    8,    8,    8, 0x0a,
     211,   42,    8,    8, 0x08,
     233,    8,    8,    8, 0x08,
     244,   42,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NotePad[] = {
    "NotePad\0\0update()\0s,c\0log(QString,QColor)\0"
    ",\0cursorInfo(int,int)\0"
    "onNodeNameUpdate(QDomNode,QString)\0"
    "onNodeDelete(QDomNode)\0parent,n\0"
    "onNodeInsert(QDomNode,QDomNode)\0"
    "onAboutToBeRemoved(QDomNode)\0"
    "onRefreshRequest()\0onLog(QString,QColor)\0"
    "onUpdate()\0onCursorInfo(int,int)\0"
};

void NotePad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NotePad *_t = static_cast<NotePad *>(_o);
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 2: _t->cursorInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onNodeNameUpdate((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->onNodeDelete((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        case 5: _t->onNodeInsert((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QDomNode(*)>(_a[2]))); break;
        case 6: _t->onAboutToBeRemoved((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        case 7: _t->onRefreshRequest(); break;
        case 8: _t->onLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 9: _t->onUpdate(); break;
        case 10: _t->onCursorInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NotePad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NotePad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NotePad,
      qt_meta_data_NotePad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NotePad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NotePad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NotePad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NotePad))
        return static_cast<void*>(const_cast< NotePad*>(this));
    return QWidget::qt_metacast(_clname);
}

int NotePad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void NotePad::update()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NotePad::log(QString _t1, QColor _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NotePad::cursorInfo(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
