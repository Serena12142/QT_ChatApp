/****************************************************************************
** Meta object code from reading C++ file 'serversocket.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Server/serversocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serversocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerSocket_t {
    const uint offsetsAndSize[44];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ServerSocket_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ServerSocket_t qt_meta_stringdata_ServerSocket = {
    {
QT_MOC_LITERAL(0, 12), // "ServerSocket"
QT_MOC_LITERAL(13, 15), // "connectionError"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(59, 11), // "socketError"
QT_MOC_LITERAL(71, 7), // "signout"
QT_MOC_LITERAL(79, 2), // "ID"
QT_MOC_LITERAL(82, 12), // "attemptLogin"
QT_MOC_LITERAL(95, 8), // "username"
QT_MOC_LITERAL(104, 8), // "password"
QT_MOC_LITERAL(113, 13), // "attemptSignup"
QT_MOC_LITERAL(127, 5), // "email"
QT_MOC_LITERAL(133, 13), // "changeProfile"
QT_MOC_LITERAL(147, 23), // "QHash<QString,QString>&"
QT_MOC_LITERAL(171, 7), // "profile"
QT_MOC_LITERAL(179, 15), // "messageReceived"
QT_MOC_LITERAL(195, 7), // "message"
QT_MOC_LITERAL(203, 11), // "getRequests"
QT_MOC_LITERAL(215, 11), // "sendRequest"
QT_MOC_LITERAL(227, 10), // "makeFriend"
QT_MOC_LITERAL(238, 13), // "deleteRequest"
QT_MOC_LITERAL(252, 11) // "onReadyRead"

    },
    "ServerSocket\0connectionError\0\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "signout\0ID\0attemptLogin\0username\0"
    "password\0attemptSignup\0email\0changeProfile\0"
    "QHash<QString,QString>&\0profile\0"
    "messageReceived\0message\0getRequests\0"
    "sendRequest\0makeFriend\0deleteRequest\0"
    "onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerSocket[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    0 /* Public */,
       5,    1,   83,    2, 0x06,    2 /* Public */,
       7,    2,   86,    2, 0x06,    4 /* Public */,
      10,    3,   91,    2, 0x06,    7 /* Public */,
      12,    1,   98,    2, 0x06,   11 /* Public */,
      15,    1,  101,    2, 0x06,   13 /* Public */,
      17,    0,  104,    2, 0x06,   15 /* Public */,
      18,    1,  105,    2, 0x06,   16 /* Public */,
      19,    1,  108,    2, 0x06,   18 /* Public */,
      20,    1,  111,    2, 0x06,   20 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    0,  114,    2, 0x08,   22 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,    8,    9,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ServerSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerSocket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->signout((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->attemptLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->attemptSignup((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->changeProfile((*reinterpret_cast< QHash<QString,QString>(*)>(_a[1]))); break;
        case 5: _t->messageReceived((*reinterpret_cast< QHash<QString,QString>(*)>(_a[1]))); break;
        case 6: _t->getRequests(); break;
        case 7: _t->sendRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->makeFriend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->deleteRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
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
            using _t = void (ServerSocket::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::connectionError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::signout)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::attemptLogin)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::attemptSignup)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(QHash<QString,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::changeProfile)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(QHash<QString,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::messageReceived)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::getRequests)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::sendRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::makeFriend)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ServerSocket::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSocket::deleteRequest)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject ServerSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ServerSocket.offsetsAndSize,
    qt_meta_data_ServerSocket,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ServerSocket_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ServerSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ServerSocket::connectionError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerSocket::signout(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerSocket::attemptLogin(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerSocket::attemptSignup(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ServerSocket::changeProfile(QHash<QString,QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ServerSocket::messageReceived(QHash<QString,QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ServerSocket::getRequests()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ServerSocket::sendRequest(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ServerSocket::makeFriend(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ServerSocket::deleteRequest(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
