#include "client.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

Client::Client(QObject *parent):
    QObject(parent),
    socket(new QTcpSocket(this))
{
    //connect to signals
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QAbstractSocket::errorOccurred, this,  &Client::serverError);
    //connect to slots
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

// ------------------------------ message from server ------------------------------

void Client::jsonReceived(const QJsonObject &data)
{
    qDebug()<<"messages";
    foreach(const QString& key, data.keys()){
        qDebug()<<key<<"->"<<data.value(key).toString();
    }
    qDebug()<<"";

    const QJsonValue typeVal = data.value(QLatin1String("type"));
    // message regarding login
    if (typeVal.toString().compare(QLatin1String("login"))==0) {
        const QJsonValue resultVal = data.value(QLatin1String("success"));
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            emit loggedIn();
            return;
        }
        const QJsonValue reasonVal = data.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    // message regarding profile
    }else if(typeVal.toString().compare(QLatin1String("profile information"))==0) {
        for(const QString& key: data.keys()) {
            if (key!="type" && key!="ID"){
                QJsonValue value = data.value(key);
                profile[key]=value.toString();
            }else if (key=="ID"){
                QJsonValue value = data.value(key);
                ID=value.toString();;
            }
        }
    }else if(typeVal.toString().compare(QLatin1String("profile change"))==0) {
        const QJsonValue resultVal = data.value(QLatin1String("success"));
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            emit profileChanged();
            return;
        }
        const QJsonValue reasonVal = data.value(QLatin1String("reason"));
        for(const QString& key: data.keys()){
            if(key!="type" and key!="success" and key!="reason"){
                QJsonValue value = data.value(key);
                profile[key]=value.toString();
            }
        }
        emit profileError(reasonVal.toString());
    // message regarding contacts
    }else if(typeVal.toString().compare(QLatin1String("message information"))==0) {
        for(const QString& key: data.keys()){
            if(key!="type"){
                QJsonArray messages_json = data[key].toArray();
                QVector<QHash<QString,QString>> messages;
                for(const QJsonValue& msg: messages_json){
                    QJsonObject message_json = msg.toObject();
                    QHash<QString,QString> message;
                    for(const QString& key2: message_json.keys()){
                        message[key2]=message_json[key2].toString();
                    }
                    messages.push_back(message);
                }
                friend_messages[key]=messages;
            }
        }
        emit informationReceived();
    }else if(typeVal.toString().compare(QLatin1String("friend information"))==0) {
        for(const QString& key: data.keys()){
            if(key!="type"){
                QJsonObject friend_profile_json = data[key].toObject();
                QHash<QString,QString> friend_profile;
                for(const QString& key2: friend_profile_json.keys()){
                    friend_profile[key2]=friend_profile_json[key2].toString();
                }
                friend_profiles[key]=friend_profile;
            }
        }
    }else if(typeVal.toString().compare(QLatin1String("message received"))==0) {
        QHash<QString,QString> message;
        for(const QString& key: data.keys()){
            if(key!="type"){
                message[key]=data[key].toString();
            }
        }
        friend_messages[message["sender"]].push_back(message);
        emit messageReceived(message);

    //received requests
    }else if(typeVal.toString().compare(QLatin1String("requests"))==0) {
        QJsonArray messages_json = data["requests"].toArray();
        QVector<QHash<QString,QString>> found_matches;
        for(const QJsonValue& msg: messages_json){
            QJsonObject message_json = msg.toObject();
            QHash<QString,QString> message;
            for(const QString& key2: message_json.keys()){
                message[key2]=message_json[key2].toString();
            }
            found_matches.push_back(message);
        }
        if (data["match"].toString()=="yes"){
            emit requestsReceived(found_matches, 1);
        }else{
            emit requestsReceived(found_matches, 0);
        }
    }else if(typeVal.toString().compare(QLatin1String("new friend"))==0) {
        for(const QString& key: data.keys()){
            if(key!="type" and key!="acceptor"){
                QJsonObject friend_profile_json = data[key].toObject();
                QHash<QString,QString> friend_profile;
                for(const QString& key2: friend_profile_json.keys()){
                    friend_profile[key2]=friend_profile_json[key2].toString();
                }
                friend_profiles[key]=friend_profile;

                QVector<QHash<QString,QString>> messages;
                friend_messages[key]=messages;

                if (data["acceptor"].toString()=="1"){
                   emit getWelcomeMessage(key);
                }

                emit newFriend();
            }
        }
    }
}

// ------------------------------ message to server ------------------------------
void Client::deleteRequest(const QString &ID){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("delete request");
    message[QStringLiteral("ID")] = ID;
    clientStream << QJsonDocument(message).toJson();
}
void Client::sendRequest(const QString &ID){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("send request");
    message[QStringLiteral("ID")] = ID;
    clientStream << QJsonDocument(message).toJson();
}
void Client::acceptRequest(const QString &ID){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("accept request");
    message[QStringLiteral("ID")] = ID;
    clientStream << QJsonDocument(message).toJson();
}
void Client::getRequests(){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("get requests");
    clientStream << QJsonDocument(message).toJson();
}

void Client::sendMessage(QHash<QString,QString> &message_sent){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("send message");
    foreach(const QString& key, message_sent.keys()) {
        message[key] = message_sent[key];
    }
    clientStream << QJsonDocument(message).toJson();
}

void Client::updateProfile(){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("profile change");
    foreach(const QString& key, profile.keys()) {
        message[key] = profile[key];
    }
    clientStream << QJsonDocument(message).toJson();
}

void Client::attemptLogin(const QString &username,const QString &password){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("login");
    message[QStringLiteral("username")] = username;
    message[QStringLiteral("password")] = password;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void Client::attemptSignup(const QString &email,const QString &username,const QString &password){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("signup");
    message[QStringLiteral("email")] = email;
    message[QStringLiteral("username")] = username;
    message[QStringLiteral("password")] = password;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void Client::signout(){
    //initialize variables
    ID="";
    profile=QHash<QString,QString>();
    friend_messages=QHash<QString,QVector<QHash<QString,QString>>>();
    friend_profiles=QHash<QString,QHash<QString,QString>>();

    // notify server
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("signout");
    clientStream << QJsonDocument(message).toJson();
}

// ------------------------------ helper functions ------------------------------

void Client::onReadyRead()
{
    // a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // a QDataStream operating on the socket
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_7);
    while(1) {
        // start a transaction so we can revert to the previous state
        // in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            // if the data is valid JSON
            if (parseError.error == QJsonParseError::NoError) {
                // if the data is JSON object
                if (jsonDoc.isObject()){
                    jsonReceived(jsonDoc.object());
                }
            }
        } else {
            // the read failed
            // the socket goes automatically back to the state it was in before the transaction started
            // exit the loop and wait for more data to become available
            break;
        }
    }
}

void Client::connectToServer()
{
    socket->connectToHost("127.0.0.1",8080);
}
