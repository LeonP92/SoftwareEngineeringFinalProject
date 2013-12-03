/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../server/server.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Server[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,    7,    7,    7, 0x09,
      57,    7,    7,    7, 0x09,
      92,   79,    7,    7, 0x09,
     136,  105,    7,    7, 0x09,
     177,  105,    7,    7, 0x09,
     263,  218,    7,    7, 0x09,
     326,  310,    7,    7, 0x09,
     369,  347,    7,    7, 0x09,
     395,  347,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Server[] = {
    "Server\0\0response\0serverResponse(QString)\0"
    "sessionOpened()\0handleClientRequest()\0"
    "clientNumber\0cleanUp(int)\0"
    "clientNumber,userName,password\0"
    "newUserRegistration(int,QString,QString)\0"
    "validateUserAccount(int,QString,QString)\0"
    "clientNumber,fromUser,toUser,subject,message\0"
    "sendEmail(int,QString,QString,QString,QString)\0"
    "clientNumber,id\0deleteEmail(int,int)\0"
    "clientNumber,userName\0getUserInbox(int,QString)\0"
    "getUserSentMail(int,QString)\0"
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Server *_t = static_cast<Server *>(_o);
        switch (_id) {
        case 0: _t->serverResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sessionOpened(); break;
        case 2: _t->handleClientRequest(); break;
        case 3: _t->cleanUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->newUserRegistration((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->validateUserAccount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->sendEmail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 7: _t->deleteEmail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->getUserInbox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->getUserSentMail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Server::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Server::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Server,
      qt_meta_data_Server, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Server::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Server))
        return static_cast<void*>(const_cast< Server*>(this));
    return QDialog::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Server::serverResponse(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
