/****************************************************************************
** Meta object code from reading C++ file 'browser.h'
**
** Created: Wed 26. May 12:52:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../browser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Browser[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x09,
      26,    8,    8,    8, 0x09,
      43,    8,    8,    8, 0x09,
      59,   57,    8,    8, 0x09,
      76,    8,    8,    8, 0x09,
      94,   92,    8,    8, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Browser[] = {
    "Browser\0\0adjustLocation()\0changeLocation()\0"
    "adjustTitle()\0p\0setProgress(int)\0"
    "finishLoading()\0k\0keyPressEvent(QKeyEvent*)\0"
};

const QMetaObject Browser::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Browser,
      qt_meta_data_Browser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Browser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Browser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Browser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Browser))
        return static_cast<void*>(const_cast< Browser*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: adjustLocation(); break;
        case 1: changeLocation(); break;
        case 2: adjustTitle(); break;
        case 3: setProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: finishLoading(); break;
        case 5: keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
