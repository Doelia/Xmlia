/****************************************************************************
** Meta object code from reading C++ file 'notepad.h'
**
** Created: Fri Mar 14 09:30:05 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "notepad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NotePad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      16,    8,    8,    8, 0x08,
      23,    8,    8,    8, 0x08,
      30,    8,    8,    8, 0x08,
      38,    8,    8,    8, 0x08,
      48,    8,    8,    8, 0x08,
      58,    8,    8,    8, 0x08,
      73,    8,    8,    8, 0x08,
      84,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NotePad[] = {
    "NotePad\0\0quit()\0open()\0save()\0toRed()\0"
    "toGreen()\0toBlack()\0onTextChange()\0"
    "onIndent()\0parse()\0"
};

void NotePad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NotePad *_t = static_cast<NotePad *>(_o);
        switch (_id) {
        case 0: _t->quit(); break;
        case 1: _t->open(); break;
        case 2: _t->save(); break;
        case 3: _t->toRed(); break;
        case 4: _t->toGreen(); break;
        case 5: _t->toBlack(); break;
        case 6: _t->onTextChange(); break;
        case 7: _t->onIndent(); break;
        case 8: _t->parse(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NotePad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NotePad::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NotePad,
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
    return QMainWindow::qt_metacast(_clname);
}

int NotePad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
