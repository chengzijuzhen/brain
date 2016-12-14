/****************************************************************************
** Meta object code from reading C++ file 'brain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../brain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Brain_t {
    QByteArrayData data[24];
    char stringdata[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Brain_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Brain_t qt_meta_stringdata_Brain = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 11),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 8),
QT_MOC_LITERAL(4, 28, 8),
QT_MOC_LITERAL(5, 37, 9),
QT_MOC_LITERAL(6, 47, 15),
QT_MOC_LITERAL(7, 63, 12),
QT_MOC_LITERAL(8, 76, 3),
QT_MOC_LITERAL(9, 80, 13),
QT_MOC_LITERAL(10, 94, 12),
QT_MOC_LITERAL(11, 107, 12),
QT_MOC_LITERAL(12, 120, 17),
QT_MOC_LITERAL(13, 138, 12),
QT_MOC_LITERAL(14, 151, 16),
QT_MOC_LITERAL(15, 168, 10),
QT_MOC_LITERAL(16, 179, 15),
QT_MOC_LITERAL(17, 195, 5),
QT_MOC_LITERAL(18, 201, 12),
QT_MOC_LITERAL(19, 214, 4),
QT_MOC_LITERAL(20, 219, 5),
QT_MOC_LITERAL(21, 225, 6),
QT_MOC_LITERAL(22, 232, 8),
QT_MOC_LITERAL(23, 241, 11)
    },
    "Brain\0canShowSkin\0\0fileOpen\0fileSave\0"
    "fileClose\0mousePressEvent\0QMouseEvent*\0"
    "eve\0showBrainOnly\0showBoneOnly\0"
    "showSkinOnly\0showBrainPoolOnly\0"
    "showAllBrain\0removeBackground\0removeBone\0"
    "unsigned short*\0image\0RegionGrow_1\0"
    "data\0width\0height\0showInfo\0getBrainVol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Brain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    1,   93,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    1,  102,    2, 0x0a /* Public */,
      18,    3,  105,    2, 0x0a /* Public */,
      22,    0,  112,    2, 0x0a /* Public */,
      23,    0,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
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
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Int, 0x80000000 | 16, QMetaType::Int, QMetaType::Int,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void Brain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Brain *_t = static_cast<Brain *>(_o);
        switch (_id) {
        case 0: _t->canShowSkin(); break;
        case 1: _t->fileOpen(); break;
        case 2: _t->fileSave(); break;
        case 3: _t->fileClose(); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->showBrainOnly(); break;
        case 6: _t->showBoneOnly(); break;
        case 7: _t->showSkinOnly(); break;
        case 8: _t->showBrainPoolOnly(); break;
        case 9: _t->showAllBrain(); break;
        case 10: _t->removeBackground(); break;
        case 11: _t->removeBone((*reinterpret_cast< unsigned short*(*)>(_a[1]))); break;
        case 12: { int _r = _t->RegionGrow_1((*reinterpret_cast< unsigned short*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: _t->showInfo(); break;
        case 14: { int _r = _t->getBrainVol();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Brain::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Brain::canShowSkin)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Brain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Brain.data,
      qt_meta_data_Brain,  qt_static_metacall, 0, 0}
};


const QMetaObject *Brain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Brain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Brain.stringdata))
        return static_cast<void*>(const_cast< Brain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Brain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Brain::canShowSkin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
