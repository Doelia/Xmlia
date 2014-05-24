/****************************************************************************
** Meta object code from reading C++ file 'notepad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Xmlia/notepad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomTabWidget_t {
    QByteArrayData data[6];
    char stringdata[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CustomTabWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CustomTabWidget_t qt_meta_stringdata_CustomTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 13),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 8),
QT_MOC_LITERAL(4, 40, 8),
QT_MOC_LITERAL(5, 49, 12)
    },
    "CustomTabWidget\0onShiftTabHit\0\0onTabHit\0"
    "onToggle\0onTabChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomTabWidget[] = {

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
       1,    0,   34,    2, 0x08,
       3,    0,   35,    2, 0x08,
       4,    0,   36,    2, 0x08,
       5,    0,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CustomTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
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

const QMetaObject CustomTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_CustomTabWidget.data,
      qt_meta_data_CustomTabWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CustomTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomTabWidget.stringdata))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_NotePad_t {
    QByteArrayData data[18];
    char stringdata[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NotePad_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NotePad_t qt_meta_stringdata_NotePad = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 6),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 3),
QT_MOC_LITERAL(4, 20, 1),
QT_MOC_LITERAL(5, 22, 1),
QT_MOC_LITERAL(6, 24, 10),
QT_MOC_LITERAL(7, 35, 16),
QT_MOC_LITERAL(8, 52, 8),
QT_MOC_LITERAL(9, 61, 1),
QT_MOC_LITERAL(10, 63, 12),
QT_MOC_LITERAL(11, 76, 12),
QT_MOC_LITERAL(12, 89, 6),
QT_MOC_LITERAL(13, 96, 18),
QT_MOC_LITERAL(14, 115, 22),
QT_MOC_LITERAL(15, 138, 5),
QT_MOC_LITERAL(16, 144, 8),
QT_MOC_LITERAL(17, 153, 12)
    },
    "NotePad\0update\0\0log\0s\0c\0cursorInfo\0"
    "onNodeNameUpdate\0QDomNode\0n\0onNodeDelete\0"
    "onNodeInsert\0parent\0onAboutToBeRemoved\0"
    "validateAndRefreshTree\0onLog\0onUpdate\0"
    "onCursorInfo\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotePad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06,
       3,    2,   70,    2, 0x06,
       6,    2,   75,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    2,   80,    2, 0x0a,
      10,    1,   85,    2, 0x0a,
      11,    2,   88,    2, 0x0a,
      13,    1,   93,    2, 0x0a,
      14,    0,   96,    2, 0x0a,
      15,    2,   97,    2, 0x08,
      16,    0,  102,    2, 0x08,
      17,    2,  103,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QColor,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,   12,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QColor,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void NotePad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NotePad *_t = static_cast<NotePad *>(_o);
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 2: _t->cursorInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onNodeNameUpdate((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->onNodeDelete((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        case 5: _t->onNodeInsert((*reinterpret_cast< QDomNode(*)>(_a[1])),(*reinterpret_cast< QDomNode(*)>(_a[2]))); break;
        case 6: _t->onAboutToBeRemoved((*reinterpret_cast< QDomNode(*)>(_a[1]))); break;
        case 7: _t->validateAndRefreshTree(); break;
        case 8: _t->onLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 9: _t->onUpdate(); break;
        case 10: _t->onCursorInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NotePad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NotePad::update)) {
                *result = 0;
            }
        }
        {
            typedef void (NotePad::*_t)(QString , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NotePad::log)) {
                *result = 1;
            }
        }
        {
            typedef void (NotePad::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NotePad::cursorInfo)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject NotePad::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NotePad.data,
      qt_meta_data_NotePad,  qt_static_metacall, 0, 0}
};


const QMetaObject *NotePad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotePad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NotePad.stringdata))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
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
