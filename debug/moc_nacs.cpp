/****************************************************************************
** Meta object code from reading C++ file 'nacs.h'
**
** Created: Wed 26. May 11:11:42 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../nacs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nacs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NACS[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      31,   22,    5,    5, 0x08,
      55,    5,    5,    5, 0x08,
      73,    5,    5,    5, 0x08,
      94,   87,    5,    5, 0x08,
     141,    5,    5,    5, 0x08,
     151,    5,    5,    5, 0x08,
     177,    5,    5,    5, 0x08,
     204,  194,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NACS[] = {
    "NACS\0\0refreshOnline()\0bSuccess\0"
    "callbackUserLogin(bool)\0showLoginDialog()\0"
    "showManager()\0reason\0"
    "iconActived(QSystemTrayIcon::ActivationReason)\0"
    "quitApp()\0triggleValidProcess(bool)\0"
    "toggleRunValid()\0szAddress\0"
    "callExplorer(QString)\0"
};

const QMetaObject NACS::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NACS,
      qt_meta_data_NACS, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NACS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NACS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NACS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NACS))
        return static_cast<void*>(const_cast< NACS*>(this));
    return QObject::qt_metacast(_clname);
}

int NACS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshOnline(); break;
        case 1: callbackUserLogin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: showLoginDialog(); break;
        case 3: showManager(); break;
        case 4: iconActived((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 5: quitApp(); break;
        case 6: triggleValidProcess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: toggleRunValid(); break;
        case 8: callExplorer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
