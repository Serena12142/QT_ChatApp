#include "server.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <time.h>
#include <sys/timeb.h>

Server::Server(QObject *parent) :
    QObject(parent),
    server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);

    if (!server->listen(QHostAddress::Any, 8080)){
        qDebug() << "Server could not start";
    }else{
        qDebug() << "Server started";
    }

    //load registered users
    QFile file("../Server/users/all_users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = data.object();
    foreach(const QString& ID, users.keys()) {
        QJsonObject user_json = users.value(ID).toObject();
        QHash<QString,QString> user;
        foreach(const QString& key, user_json.keys()) {
            user.insert(key,user_json.value(key).toString());
        }
        all_users.insert(ID,user);
        registered_usernames.insert(user["username"],ID);
        registered_emails.insert(user["email"],ID);
    }

    //remove_user(registered_usernames["cathy"]);

}

Server::~Server(){

}

QString Server::new_ID(){
    QString id_;
    int length = 32;
    QString strTmp = "abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    struct timeb timer;
    ftime(&timer);
    srand(timer.time * 1000 + timer.millitm);

    for(int i = 0; i < length; i++ )
    {
        int j = rand()%61;
        id_ += strTmp.at(j);
    }
    // qDebug() << id_;
    if(all_users.contains(id_)==0){
        return id_;
    }else{
        qDebug()<<"something went wrong";
        return new_ID();
    }
    return "error";
}

void Server::getRequests(ServerSocket* client){
    //get current friends
    QDir dir("../Server/messages/"+client->ID);
    QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files);
    QSet<QString> friend_IDs;
    for(const QString& friend_ID: files){
        friend_IDs.insert(friend_ID.split('.')[0]);
    }

    //get matches
    QVector<QHash<QString,QString>> matches;
    //currently returns all users, change later *** dont give already requested people!
    for(const QString& key: all_users.keys()){
        if (key!=client->ID && friend_IDs.contains(key)==0){
            QHash<QString,QString> match;
            match["ID"]=key;
            match["username"]=all_users[key]["username"];
            matches.push_back(match);
        }
    }
    client->returnRequests(matches, all_users, 1);

    //get existing requests
    QFile file("../Server/friend_requests.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject all_requests = data.object();
    QJsonObject incoming_requests = all_requests.value(client->ID).toObject();
    QVector<QHash<QString,QString>> requests;
    for(const QString& key: incoming_requests.keys()){
        //clear invalid (user donesn't exist) requests ***
        //if key not in all users
        //  remove key from incoming_requests
        //  continue
        //clear expired (need server time and add time to requests) ***
        //if expired
        //  countinue

        QHash<QString,QString> request;
        request["ID"]=key;
        request["username"]=incoming_requests.value(key).toObject().value("username").toString();
        //request["time"]=incoming_requests.value(key).toObject().value("time").toString();
        requests.push_back(request);
    }
    client->returnRequests(requests, all_users, 0);
    //save back to local
    all_requests.insert(client->ID,incoming_requests);
    data.setObject(all_requests);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(data.toJson());
    file.close();
}

void Server::messageReceived(ServerSocket* client, QHash<QString,QString> &message){
    //message
    QJsonObject message_json;
    for(const QString& key: message.keys()){
        message_json.insert(key,message[key]);
    }
    QString sender=client->ID;
    QString receiver=message["receiver"];
    //save to sender side
    QFile file("../Server/messages/"+sender+"/"+receiver+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonArray jsonArray=jsonDoc.array();
    jsonArray.push_back(message_json);
    jsonDoc.setArray(jsonArray);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    //save to receiver side
    file.setFileName("../Server/messages/"+receiver+"/"+sender+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();
    jsonArray=jsonDoc.array();
    jsonArray.push_back(message_json);
    jsonDoc.setArray(jsonArray);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    //notify receiver if active
    if (active_users.contains(receiver)){
        for (ServerSocket* receiving_client:clients){
            if (receiving_client->ID==receiver){
                receiving_client->sendMessage(message_json);
            }
        }
    }
}

void Server::remove_user(const QString &ID){
    //active
    //force signout the user
    //remove from all_users, registered_emails, and registered_usernames
    //notify and remove from all active friends

    //permanent
    //remove from all_users.json
    QFile file("../Server/all_users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = data.object();
    users.remove(ID);
    data.setObject(users);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(data.toJson());
    file.close();
    //remove from all friend folders
    QDir dir("../Server/messages/"+ID);
    QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files);
    foreach(const QString& friend_ID, files) {
        QFile friend_message("../Server/messages/"+friend_ID.split('.')[0]+"/"+ID+".json");
        friend_message.remove();
    }
    //remove folder from messages
    dir.removeRecursively();
}

void Server::sendRequest(ServerSocket *client, const QString &receiver_ID){
    //save request to local
    QFile file("../Server/friend_requests.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject requests = data.object();
    QJsonObject specific = requests.value(receiver_ID).toObject();
    QJsonObject request;
    request.insert("username",all_users[client->ID]["username"]);
    //request.insert("time", <some server time>) ***
    specific.insert(client->ID,request);
    requests.insert(receiver_ID,specific);
    data.setObject(requests);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(data.toJson());
    file.close();
}


void Server::makeFriend(ServerSocket *client, const QString &ID2){
    QString ID1=client->ID;

    //check if user exists***

    //save on server side
    //create message json file for ID1
    QFile file("../Server/messages/"+ID1+"/"+ID2+".json");
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    QJsonArray jsonArray;
    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray);
    file.write(jsonDoc.toJson());
    file.close();
    //create message json file for ID2
    QFile file2("../Server/messages/"+ID2+"/"+ID1+".json");
    file2.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    QJsonArray jsonArray2;
    QJsonDocument jsonDoc2;
    jsonDoc2.setArray(jsonArray2);
    file2.write(jsonDoc2.toJson());
    file2.close();

    //notify clients
    //receiver
    if (active_users.contains(ID2)){
        for (ServerSocket* receiving_client:clients){
            if (receiving_client->ID==ID2){
                receiving_client->newFriend(ID1, false, all_users);
            }
        }
    }
    //sender
    client->newFriend(ID2, true, all_users);

    //remove request from local
    QFile file3("../Server/friend_requests.json");
    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file3.readAll());
    file3.close();
    QJsonObject requests = data.object();
    QJsonObject specific = requests.value(ID1).toObject();
    specific.remove(ID2);
    requests[ID1]=specific;
    data.setObject(requests);
    file3.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file3.write(data.toJson());
    file3.close();
}

void Server::deleteRequest(ServerSocket *client, const QString &ID2){
    //remove request from local
    QString ID1=client->ID;
    QFile file3("../Server/friend_requests.json");
    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file3.readAll());
    file3.close();
    QJsonObject requests = data.object();
    QJsonObject specific = requests.value(ID1).toObject();
    specific.remove(ID2);
    requests[ID1]=specific;
    data.setObject(requests);
    file3.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file3.write(data.toJson());
    file3.close();
}

void Server::attemptSignup(ServerSocket *client,const QString &email,const QString &username,const QString &password){
    if(registered_emails.contains(email)){
        client->loginError("Email already taken");
    }else if(registered_usernames.contains(username)){
        client->loginError("Username already taken");
    }else{
        QString ID=new_ID();
        client->loginSuccessful(ID);
        active_users.append(ID);

        //initialize and save client info
        QHash<QString,QString> user;
        user.insert("username",username);
        user.insert("password",password);
        user.insert("email",email);
        user.insert("intro","This is your intro.");
        user.insert("pronoun","");
        user.insert("language1","");
        user.insert("language2","");
        user.insert("language3","");
        user.insert("profile_pic_path", ":/images/pic/profile.png");
        all_users.insert(ID,user);
        registered_usernames.insert(username,ID);
        registered_emails.insert(email,ID);

        //save to json file
        QFile file("../Server/all_users.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonDocument data = QJsonDocument::fromJson(file.readAll());
        file.close();
        QJsonObject users = data.object();
        QJsonObject user_json;
        foreach(const QString& key, user.keys()) {
            user_json.insert(key,user[key]);
        }
        users.insert(ID,user_json);
        data.setObject(users);
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(data.toJson());
        file.close();

        //initialize and save messages info
        QDir().mkdir("../Server/messages/"+ID);

        //send info to client
        client->sendPersonalInfo(user);
        client->sendFriendMessageInfo(ID,all_users);
    }
}

void Server::attemptLogin(ServerSocket *client,const QString &username,const QString &password){
    if(registered_usernames.contains(username)){
        if(all_users[registered_usernames[username]]["password"].compare(password)==0){
            client->loginSuccessful(registered_usernames[username]);
            active_users.append(registered_usernames[username]);
            //get client info and send
            client->sendPersonalInfo(all_users[registered_usernames[username]]);
            //get message info and send
            client->sendFriendMessageInfo(registered_usernames[username], all_users);

            qDebug()<<"Current users:";
            foreach(const QString& ID, active_users) {
                qDebug()<<ID<<": "<<all_users[ID]["username"];
            }
            qDebug()<<"";
        }else{
            client->loginError("Incorrect password");
        }
    }else if(registered_emails.contains(username)){
        if(all_users[registered_emails[username]]["password"].compare(password)==0){
            client->loginSuccessful(registered_emails[username]);
            active_users.append(registered_emails[username]);
            //get client info and send
            client->sendPersonalInfo(all_users[registered_emails[username]]);
            //get message info and send
            client->sendFriendMessageInfo(registered_emails[username], all_users);

            qDebug()<<"Current users:";
            foreach(const QString& ID, active_users) {
                qDebug()<<ID<<": "<<all_users[ID]["username"];
            }
            qDebug()<<"";
        }else{
            client->loginError("Incorrect password");
        }
    }else{
        client->loginError("Username does not exist");
    }
}

void Server::changeProfile(ServerSocket* client, QHash<QString,QString> profile){
    //if username changed
    if(profile["username"]!=all_users[client->ID]["username"]){
        qDebug()<<profile["username"]<<" vs "<<all_users[client->ID]["username"];
        if (registered_usernames.contains(profile["username"])){
            client->changeProfileError("username is already taken",all_users[client->ID]);
            return;
        }
    }
    //if email changed
    if(profile["email"]!=all_users[client->ID]["email"]){
        if (registered_emails.contains(profile["email"])){
            client->changeProfileError("email is already taken",all_users[client->ID]);
            return;
        }
    }
    //approve change
    client->changeProfileSuccess();

    registered_usernames.remove(all_users[client->ID]["username"]);
    registered_usernames.insert(profile["username"],client->ID);
    registered_emails.remove(all_users[client->ID]["email"]);
    registered_emails.insert(profile["email"],client->ID);
    all_users[client->ID]=profile;

    //save to json
    QFile file("../Server/all_users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject users = data.object();
    QJsonObject profile_json;
    foreach(const QString& key, profile.keys()) {
        profile_json.insert(key,profile[key]);
    }
    users[client->ID]=profile_json;
    data.setObject(users);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(data.toJson());
    file.close();

    //update active friends ***

}

void Server::newConnection(){
    ServerSocket *client = new ServerSocket(this);
    client->setSocket(server->nextPendingConnection());
    connect(client, &ServerSocket::connectionError, this,
            std::bind(&Server::userConnectionError, this, client, std::placeholders::_1));
    connect(client, &ServerSocket::attemptLogin, this,
            std::bind(&Server::attemptLogin, this, client, std::placeholders::_1, std::placeholders::_2));
    connect(client, &ServerSocket::attemptSignup, this,
            std::bind(&Server::attemptSignup, this, client, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    connect(client, &ServerSocket::changeProfile, this,
            std::bind(&Server::changeProfile, this, client, std::placeholders::_1));
    connect(client, &ServerSocket::signout, this, &Server::signout);
    connect(client, &ServerSocket::messageReceived, this,
            std::bind(&Server::messageReceived, this, client, std::placeholders::_1));
    connect(client, &ServerSocket::getRequests, this,
            std::bind(&Server::getRequests, this, client));

    connect(client, &ServerSocket::sendRequest, this,
            std::bind(&Server::sendRequest, this, client, std::placeholders::_1));
    connect(client, &ServerSocket::makeFriend, this,
            std::bind(&Server::makeFriend, this, client, std::placeholders::_1));
    connect(client, &ServerSocket::deleteRequest, this,
            std::bind(&Server::deleteRequest, this, client, std::placeholders::_1));

    clients.append(client);
    qDebug() << "New client Connected";
}

void Server::signout(const QString &ID){
    active_users.removeOne(ID);

    qDebug()<<"Current users:";
    foreach(const QString& ID, active_users) {
        qDebug()<<ID<<": "<<all_users[ID]["username"];
    }
    qDebug()<<"";
}

void Server::userConnectionError(ServerSocket *client, QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "The client closed the connection";
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() << "Operation timed out";
        return;
    case QAbstractSocket::TemporaryError:
        qDebug() << "A Temporary error occured";
        return;
    case QAbstractSocket::OperationError:
        qDebug() << "Operation failed, please try again";
        return;
    default:
        qDebug() << "An unknown error occured";
    }
    clients.removeAll(client);
    active_users.removeOne(client->ID);
    client->deleteLater();

    qDebug()<<"Current users:";
    foreach(const QString& ID, active_users) {
        qDebug()<<ID<<": "<<all_users[ID]["username"];
    }
    qDebug()<<"";
}
