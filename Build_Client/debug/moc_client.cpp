/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Client/client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    const uint offsetsAndSize[60];
    char stringdata0[374];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 6), // "Client"
QT_MOC_LITERAL(7, 9), // "connected"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 11), // "serverError"
QT_MOC_LITERAL(30, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(59, 11), // "socketError"
QT_MOC_LITERAL(71, 10), // "loginError"
QT_MOC_LITERAL(82, 6), // "reason"
QT_MOC_LITERAL(89, 8), // "loggedIn"
QT_MOC_LITERAL(98, 19), // "informationReceived"
QT_MOC_LITERAL(118, 14), // "profileChanged"
QT_MOC_LITERAL(133, 12), // "profileError"
QT_MOC_LITERAL(146, 15), // "messageReceived"
QT_MOC_LITERAL(162, 23), // "QHash<QString,QString>&"
QT_MOC_LITERAL(186, 7), // "message"
QT_MOC_LITERAL(194, 16), // "requestsReceived"
QT_MOC_LITERAL(211, 29), // "QList<QHash<QString,QString>>"
QT_MOC_LITERAL(241, 8), // "requests"
QT_MOC_LITERAL(250, 5), // "match"
QT_MOC_LITERAL(256, 17), // "getWelcomeMessage"
QT_MOC_LITERAL(274, 2), // "ID"
QT_MOC_LITERAL(277, 9), // "newFriend"
QT_MOC_LITERAL(287, 12), // "attemptLogin"
QT_MOC_LITERAL(300, 8), // "username"
QT_MOC_LITERAL(309, 8), // "password"
QT_MOC_LITERAL(318, 13), // "attemptSignup"
QT_MOC_LITERAL(332, 5), // "email"
QT_MOC_LITERAL(338, 11), // "sendMessage"
QT_MOC_LITERAL(350, 11), // "getRequests"
QT_MOC_LITERAL(362, 11) // "onReadyRead"

    },
    "Client\0connected\0\0serverError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "loginError\0reason\0loggedIn\0"
    "informationReceived\0profileChanged\0"
    "profileError\0messageReceived\0"
    "QHash<QString,QString>&\0message\0"
    "requestsReceived\0QList<QHash<QString,QString>>\0"
    "requests\0match\0getWelcomeMessage\0ID\0"
    "newFriend\0attemptLogin\0username\0"
    "password\0attemptSignup\0email\0sendMessage\0"
    "getRequests\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    0 /* Public */,
       3,    1,  111,    2, 0x06,    1 /* Public */,
       6,    1,  114,    2, 0x06,    3 /* Public */,
       8,    0,  117,    2, 0x06,    5 /* Public */,
       9,    0,  118,    2, 0x06,    6 /* Public */,
      10,    0,  119,    2, 0x06,    7 /* Public */,
      11,    1,  120,    2, 0x06,    8 /* Public */,
      12,    1,  123,    2, 0x06,   10 /* Public */,
      15,    2,  126,    2, 0x06,   12 /* Public */,
      19,    1,  131,    2, 0x06,   15 /* Public */,
      21,    0,  134,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      22,    2,  135,    2, 0x0a,   18 /* Public */,
      25,    3,  140,    2, 0x0a,   21 /* Public */,
      27,    1,  147,    2, 0x0a,   25 /* Public */,
      28,    0,  150,    2, 0x0a,   27 /* Public */,
      29,    0,  151,    2, 0x08,   28 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   26,   23,   24,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->serverError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->loginError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->loggedIn(); break;
        case 4: _t->informationReceived(); break;
        case 5: _t->profileChanged(); break;
        case 6: _t->profileError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->messageReceived((*reinterpret_cast< QHash<QString,QString>(*)>(_a[1]))); break;
        case 8: _t->requestsReceived((*reinterpret_cast< QList<QHash<QString,QString>>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->getWelcomeMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->newFriend(); break;
        case 11: _t->attemptLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: _t->attemptSignup((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 13: _t->sendMessage((*reinterpret_cast< QHash<QString,QString>(*)>(_a[1]))); break;
        case 14: _t->getRequests(); break;
        case 15: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Client::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::serverError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::loginError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::loggedIn)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::informationReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::profileChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::profileError)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Client::*)(QHash<QString,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::messageReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Client::*)(QVector<QHash<QString,QString>> , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::requestsReceived)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::getWelcomeMessage)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::newFriend)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Client.offsetsAndSize,
    qt_meta_data_Client,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Client_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<QHash<QString,QString>>, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Client::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::serverError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Client::informationReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Client::profileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Client::profileError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Client::messageReceived(QHash<QString,QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Client::requestsReceived(QVector<QHash<QString,QString>> _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Client::getWelcomeMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Client::newFriend()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
