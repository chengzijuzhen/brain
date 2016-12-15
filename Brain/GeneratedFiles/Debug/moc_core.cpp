/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Core_t {
    QByteArrayData data[21];
    char stringdata[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core_t qt_meta_stringdata_Core = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 11),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 13),
QT_MOC_LITERAL(4, 32, 12),
QT_MOC_LITERAL(5, 45, 12),
QT_MOC_LITERAL(6, 58, 17),
QT_MOC_LITERAL(7, 76, 12),
QT_MOC_LITERAL(8, 89, 16),
QT_MOC_LITERAL(9, 106, 10),
QT_MOC_LITERAL(10, 117, 15),
QT_MOC_LITERAL(11, 133, 5),
QT_MOC_LITERAL(12, 139, 12),
QT_MOC_LITERAL(13, 152, 4),
QT_MOC_LITERAL(14, 157, 5),
QT_MOC_LITERAL(15, 163, 6),
QT_MOC_LITERAL(16, 170, 8),
QT_MOC_LITERAL(17, 179, 11),
QT_MOC_LITERAL(18, 191, 7),
QT_MOC_LITERAL(19, 199, 7),
QT_MOC_LITERAL(20, 207, 10)
    },
    "Core\0canShowSkin\0\0showBrainOnly\0"
    "showBoneOnly\0showSkinOnly\0showBrainPoolOnly\0"
    "showAllBrain\0removeBackground\0removeBone\0"
    "unsigned short*\0image\0RegionGrow_1\0"
    "data\0width\0height\0showInfo\0getBrainVol\0"
    "restore\0showAll\0freeMemory"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
      12,    3,   94,    2, 0x0a /* Public */,
      16,    0,  101,    2, 0x0a /* Public */,
      17,    0,  102,    2, 0x0a /* Public */,
      18,    0,  103,    2, 0x0a /* Public */,
      19,    0,  104,    2, 0x0a /* Public */,
      20,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Int, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Core *_t = static_cast<Core *>(_o);
        switch (_id) {
        case 0: _t->canShowSkin(); break;
        case 1: _t->showBrainOnly(); break;
        case 2: _t->showBoneOnly(); break;
        case 3: _t->showSkinOnly(); break;
        case 4: _t->showBrainPoolOnly(); break;
        case 5: _t->showAllBrain(); break;
        case 6: _t->removeBackground(); break;
        case 7: _t->removeBone((*reinterpret_cast< unsigned short*(*)>(_a[1]))); break;
        case 8: { int _r = _t->RegionGrow_1((*reinterpret_cast< unsigned short*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: _t->showInfo(); break;
        case 10: { int _r = _t->getBrainVol();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: _t->restore(); break;
        case 12: _t->showAll(); break;
        case 13: _t->freeMemory(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Core::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Core::canShowSkin)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Core::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Core.data,
      qt_meta_data_Core,  qt_static_metacall, 0, 0}
};


const QMetaObject *Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Core.stringdata))
        return static_cast<void*>(const_cast< Core*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Core::canShowSkin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
