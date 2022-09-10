/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Server/server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Server_t {
    const uint offsetsAndSize[54];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Server_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Server_t qt_meta_stringdata_Server = {
    {
QT_MOC_LITERAL(0, 6), // "Server"
QT_MOC_LITERAL(7, 13), // "newConnection"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 19), // "userConnectionError"
QT_MOC_LITERAL(42, 13), // "ServerSocket*"
QT_MOC_LITERAL(56, 6), // "client"
QT_MOC_LITERAL(63, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(92, 11), // "socketError"
QT_MOC_LITERAL(104, 7), // "signout"
QT_MOC_LITERAL(112, 2), // "ID"
QT_MOC_LITERAL(115, 12), // "attemptLogin"
QT_MOC_LITERAL(128, 8), // "username"
QT_MOC_LITERAL(137, 8), // "password"
QT_MOC_LITERAL(146, 13), // "attemptSignup"
QT_MOC_LITERAL(160, 5), // "email"
QT_MOC_LITERAL(166, 13), // "changeProfile"
QT_MOC_LITERAL(180, 22), // "QHash<QString,QString>"
QT_MOC_LITERAL(203, 7), // "profile"
QT_MOC_LITERAL(211, 15), // "messageReceived"
QT_MOC_LITERAL(227, 23), // "QHash<QString,QString>&"
QT_MOC_LITERAL(251, 7), // "message"
QT_MOC_LITERAL(259, 11), // "getRequests"
QT_MOC_LITERAL(271, 11), // "sendRequest"
QT_MOC_LITERAL(283, 11), // "receiver_ID"
QT_MOC_LITERAL(295, 10), // "makeFriend"
QT_MOC_LITERAL(306, 3), // "ID2"
QT_MOC_LITERAL(310, 13) // "deleteRequest"

    },
    "Server\0newConnection\0\0userConnectionError\0"
    "ServerSocket*\0client\0QAbstractSocket::SocketError\0"
    "socketError\0signout\0ID\0attemptLogin\0"
    "username\0password\0attemptSignup\0email\0"
    "changeProfile\0QHash<QString,QString>\0"
    "profile\0messageReceived\0QHash<QString,QString>&\0"
    "message\0getRequests\0sendRequest\0"
    "receiver_ID\0makeFriend\0ID2\0deleteRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    0 /* Private */,
       3,    2,   81,    2, 0x08,    1 /* Private */,
       8,    1,   86,    2, 0x08,    4 /* Private */,
      10,    3,   89,    2, 0x08,    6 /* Private */,
      13,    4,   96,    2, 0x08,   10 /* Private */,
      15,    2,  105,    2, 0x08,   15 /* Private */,
      18,    2,  110,    2, 0x08,   18 /* Private */,
      21,    1,  115,    2, 0x08,   21 /* Private */,
      22,    2,  118,    2, 0x08,   23 /* Private */,
      24,    2,  123,    2, 0x08,   26 /* Private */,
      26,    2,  128,    2, 0x08,   29 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString, QMetaType::QString,    5,   11,   12,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,   14,   11,   12,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 16,    5,   17,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 19,    5,   20,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    5,   23,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    5,   25,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    5,   25,

       0        // eod
};

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Server *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newConnection(); break;
        case 1: _t->userConnectionError((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[2]))); break;
        case 2: _t->signout((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->attemptLogin((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->attemptSignup((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 5: _t->changeProfile((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< QHash<QString,QString>(*)>(_a[2]))); break;
        case 6: _t->messageReceived((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< QHash<QString,QString>(*)>(_a[2]))); break;
        case 7: _t->getRequests((*reinterpret_cast< ServerSocket*(*)>(_a[1]))); break;
        case 8: _t->sendRequest((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->makeFriend((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->deleteRequest((*reinterpret_cast< ServerSocket*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ServerSocket* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Server::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Server.offsetsAndSize,
    qt_meta_data_Server,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Server_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<QHash<QString,QString> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ServerSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>


>,
    nullptr
} };


const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Server.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
