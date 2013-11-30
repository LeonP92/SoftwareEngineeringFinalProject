/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x09,
      38,    7,    7,    7, 0x09,
      56,    7,    7,    7, 0x09,
      72,    7,    7,    7, 0x09,
      87,    7,    7,    7, 0x09,
      95,    7,    7,    7, 0x09,
     109,    7,    7,    7, 0x09,
     122,    7,    7,    7, 0x09,
     138,    7,    7,    7, 0x09,
     157,    7,    7,    7, 0x09,
     171,    7,    7,    7, 0x09,
     191,  179,    7,    7, 0x09,
     234,    7,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0enableStartConnectionButton()\0"
    "startConnection()\0sessionOpened()\0"
    "registerUser()\0login()\0viewMessage()\0"
    "newMessage()\0deleteMessage()\0"
    "viewSentMessages()\0sendMessage()\0"
    "reply()\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "readServerResponse()\0"
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Client *_t = static_cast<Client *>(_o);
        switch (_id) {
        case 0: _t->enableStartConnectionButton(); break;
        case 1: _t->startConnection(); break;
        case 2: _t->sessionOpened(); break;
        case 3: _t->registerUser(); break;
        case 4: _t->login(); break;
        case 5: _t->viewMessage(); break;
        case 6: _t->newMessage(); break;
        case 7: _t->deleteMessage(); break;
        case 8: _t->viewSentMessages(); break;
        case 9: _t->sendMessage(); break;
        case 10: _t->reply(); break;
        case 11: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->readServerResponse(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Client::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Client::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QDialog::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
