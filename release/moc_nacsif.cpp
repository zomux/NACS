/****************************************************************************
** Meta object code from reading C++ file 'nacsif.h'
**
** Created: Wed 26. May 12:53:03 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../nacsif.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nacsif.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NACSIF[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   17,    8,    7, 0x09,
      93,   64,   59,    7, 0x09,
     134,  124,   59,    7, 0x09,
     169,  152,   59,    7, 0x09,
     211,  198,   59,    7, 0x09,
     249,    7,  241,    7, 0x09,
     269,  265,  241,    7, 0x09,
     293,  283,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_NACSIF[] = {
    "NACSIF\0\0QVariant\0szCommand,param\0"
    "command(QString,QVariant)\0bool\0"
    "szSourceVol,szName,szDestVol\0"
    "mount(QString,QString,QString)\0szDestVol\0"
    "dismount(QString)\0szVol,Name,nSize\0"
    "format(QString,QString,long)\0szName,szVol\0"
    "deleteFormat(QString,QString)\0QString\0"
    "getDiskSerial()\0str\0hash(QString)\0"
    "szAddress\0callExplorer(QString)\0"
};

const QMetaObject NACSIF::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NACSIF,
      qt_meta_data_NACSIF, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NACSIF::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NACSIF::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NACSIF::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NACSIF))
        return static_cast<void*>(const_cast< NACSIF*>(this));
    return QObject::qt_metacast(_clname);
}

int NACSIF::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QVariant _r = command((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 1: { bool _r = mount((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = dismount((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = format((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = deleteFormat((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { QString _r = getDiskSerial();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = hash((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: callExplorer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
