#include "serversocket.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>

ServerSocket::ServerSocket(QObject *parent) :
    QObject(parent)
{
    ID="";
}

void ServerSocket::setSocket(QTcpSocket *clientSocket){
    socket = clientSocket;
    //connect to signals
    connect(socket, &QAbstractSocket::errorOccurred, this, &ServerSocket::connectionError);
    //connect to slots
    connect(socket, &QTcpSocket::readyRead, this, &ServerSocket::onReadyRead);
}

ServerSocket::~ServerSocket(){
    delete socket;
}

void ServerSocket::newFriend(const QString& ID, bool acceptor, QHash<QString,QHash<QString,QString>> &all_users){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);

    QJsonObject friendInfo;
    friendInfo[QStringLiteral("type")] = QStringLiteral("new friend");
    friendInfo[QStringLiteral("acceptor")] = acceptor ? "1" : "0";;
    QJsonObject friendprofile;
    for(const QString& key: all_users[ID].keys()) {
        if(key!="password"){
            friendprofile[key]=all_users[ID][key];
        }
    }
    friendInfo.insert(ID,friendprofile);
    clientStream << QJsonDocument(friendInfo).toJson();
}

void ServerSocket::returnRequests(QVector<QHash<QString,QString>> requests,
                                  QHash<QString,QHash<QString,QString>> &all_users, int match){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("requests");
    QJsonObject friendInfo;
    friendInfo[QStringLiteral("type")] = QStringLiteral("friend information");

    QJsonArray matches_json;
    for(const QHash<QString,QString>& match:requests)
    {
        QJsonObject match_json;
        for (const QString& key:match.keys()){
            match_json[key]=match[key];
        }
        matches_json.push_back(match_json);

        QJsonObject friendprofile;
        for(const QString& key: all_users[match["ID"]].keys()) {
            if(key!="password"){
                friendprofile[key]=all_users[match["ID"]][key];
            }
        }
        friendInfo.insert(match["ID"],friendprofile);
    }
    message[QStringLiteral("requests")] = matches_json;
    if (match){
        message[QStringLiteral("match")] = "yes";
    }else{
        message[QStringLiteral("match")] = "no";
    }

    // send the JSON using QDataStream
    clientStream << QJsonDocument(friendInfo).toJson();
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::sendMessage(QJsonObject &message){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    message[QStringLiteral("type")] = QStringLiteral("message received");
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::sendFriendMessageInfo(const QString &ID, QHash<QString,QHash<QString,QString>> &all_users){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject messageInfo;
    QJsonObject friendInfo;
    messageInfo[QStringLiteral("type")] = QStringLiteral("message information");
    friendInfo[QStringLiteral("type")] = QStringLiteral("friend information");
    QDir dir("../Server/messages/"+ID);
    QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files);
    for(const QString& friend_ID: files) {
        QFile message_file("../Server/messages/"+ID+"/"+friend_ID.split('.')[0]+".json");
        message_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonDocument data = QJsonDocument::fromJson(message_file.readAll());
        message_file.close();
        QJsonArray friend_messages= data.array();
        messageInfo[friend_ID.split('.')[0]] = friend_messages;
        QJsonObject friendprofile;
        for(const QString& key: all_users[friend_ID.split('.')[0]].keys()) {
            if(key!="password"){
                friendprofile[key]=all_users[friend_ID.split('.')[0]][key];
            }
        }
        friendInfo.insert(friend_ID.split('.')[0],friendprofile);
    }
    // send the JSON using QDataStream
    clientStream << QJsonDocument(friendInfo).toJson();
    clientStream << QJsonDocument(messageInfo).toJson();
}

void ServerSocket::sendPersonalInfo(QHash<QString,QString> &user){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("profile information");
    message[QStringLiteral("ID")] = ID;
    for(QHash<QString,QString>::iterator i=user.begin(); i!=user.end(); ++i)
    {
        message[i.key()] = i.value();
    }
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::changeProfileSuccess(){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("profile change");
    message[QStringLiteral("success")] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::changeProfileError(const QString &reason, QHash<QString,QString> &profile){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("profile change");
    message[QStringLiteral("success")] = false;
    message[QStringLiteral("reason")] = reason;
    foreach(const QString& key, profile.keys()) {
        message[key] = profile[key];
    }
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::loginSuccessful(const QString &ID){
    this->ID=ID;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("login");
    message[QStringLiteral("success")] = true;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::loginError(const QString &reason){
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("login");
    message[QStringLiteral("success")] = false;
    message[QStringLiteral("reason")] = reason;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

void ServerSocket::jsonReceived(const QJsonObject &data)
{
    qDebug()<<"message";
    foreach(const QString& key, data.keys()){
        qDebug()<<key<<"->"<<data.value(key).toString();
    }
    qDebug()<<"";

    const QJsonValue typeVal = data.value(QLatin1String("type"));
    // message regarding login
    if (typeVal.toString().compare(QLatin1String("login"))==0) {
        const QJsonValue usernameVal = data.value(QLatin1String("username"));
        const QString username = usernameVal.toString();
        const QJsonValue passwordVal = data.value(QLatin1String("password"));
        const QString password = passwordVal.toString();
        emit attemptLogin(username,password);
    }else if (typeVal.toString().compare(QLatin1String("signup"))==0) {
        const QJsonValue emailVal = data.value(QLatin1String("email"));
        const QString email = emailVal.toString();
        const QJsonValue usernameVal = data.value(QLatin1String("username"));
        const QString username = usernameVal.toString();
        const QJsonValue passwordVal = data.value(QLatin1String("password"));
        const QString password = passwordVal.toString();
        emit attemptSignup(email,username,password);
    //change profile
    }else if (typeVal.toString().compare(QLatin1String("profile change"))==0) {
        QHash<QString,QString> profile;
        foreach(const QString& key, data.keys()){
            if(key!="type"){
                profile.insert(key,data.value(key).toString());
            }
        }
        emit changeProfile(profile);
    //received message
    }else if (typeVal.toString().compare(QLatin1String("send message"))==0) {
        QHash<QString,QString> message;
        foreach(const QString& key, data.keys()){
            if(key!="type"){
                message.insert(key,data.value(key).toString());
            }
        }
        emit messageReceived(message);
    //matching
    }else if (typeVal.toString().compare(QLatin1String("get requests"))==0) {
        emit getRequests();
    }else if (typeVal.toString().compare(QLatin1String("send request"))==0) {
        emit sendRequest(data.value("ID").toString());
    }else if (typeVal.toString().compare(QLatin1String("accept request"))==0) {
        emit makeFriend(data.value("ID").toString());
    }else if (typeVal.toString().compare(QLatin1String("delete request"))==0) {
        emit deleteRequest(data.value("ID").toString());
    //signout
    }else if (typeVal.toString().compare(QLatin1String("signout"))==0) {
        emit signout(ID);
        ID="";
    }
}


// ------------------------------ helper functions ------------------------------

void ServerSocket::onReadyRead()
{
    // a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // a QDataStream operating on the socket
    QDataStream socketStream(socket);
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
