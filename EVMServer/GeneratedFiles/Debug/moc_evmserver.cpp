/****************************************************************************
** Meta object code from reading C++ file 'evmserver.h'
**
** Created: Wed 30. Sep 12:31:17 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../evmserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evmserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EVMServer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      30,   27,   10,   10, 0x0a,
      55,   10,   10,   10, 0x0a,
      70,   10,   10,   10, 0x0a,
      93,   88,   10,   10, 0x0a,
     116,   10,   10,   10, 0x0a,
     136,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EVMServer[] = {
    "EVMServer\0\0setDataOnPlot()\0pe\0"
    "wheelEvent(QWheelEvent*)\0clickConnect()\0"
    "clickDisConnect()\0mode\0setDataOnPlot_upd(int)\0"
    "changePacketsLeft()\0changePacketsRight()\0"
};

const QMetaObject EVMServer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EVMServer,
      qt_meta_data_EVMServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EVMServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EVMServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EVMServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EVMServer))
        return static_cast<void*>(const_cast< EVMServer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EVMServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setDataOnPlot(); break;
        case 1: wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 2: clickConnect(); break;
        case 3: clickDisConnect(); break;
        case 4: setDataOnPlot_upd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: changePacketsLeft(); break;
        case 6: changePacketsRight(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
