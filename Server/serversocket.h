#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include <QTcpSocket>

class ServerSocket : public QObject{
    Q_OBJECT

public:
    explicit ServerSocket(QObject *parent = nullptr);
    ~ServerSocket();
    void setSocket(QTcpSocket *socket);
    void disconnectFromClient();

    void loginSuccessful(const QString &username);
    void loginError(const QString &reason);
    QString ID;

    void sendPersonalInfo(QHash<QString,QString> &user);
    void changeProfileSuccess();
    void changeProfileError(const QString &reason, QHash<QString,QString> &profile);

    void sendFriendMessageInfo(const QString &ID, QHash<QString,QHash<QString,QString>> &all_users);
    void sendMessage(QJsonObject &message);

    void returnRequests(QVector<QHash<QString,QString>> matches,
                        QHash<QString,QHash<QString,QString>> &all_users, int match);
    void newFriend(const QString& ID, bool acceptor, QHash<QString,QHash<QString,QString>> &all_users);

private:
    QTcpSocket *socket;
    void jsonReceived(const QJsonObject &data);

signals:
    //QTcpSocket signals
    void connectionError(QAbstractSocket::SocketError socketError);
    void signout(const QString &ID);

    //signals fired after analyzing message from the client
    void attemptLogin(const QString &username,const QString &password);
    void attemptSignup(const QString &email,const QString &username,const QString &password);
    void changeProfile(QHash<QString,QString> &profile);

    //chat related
    void messageReceived(QHash<QString,QString> &message);

    //matching
    void getRequests();
    void sendRequest(const QString &ID);
    void makeFriend(const QString &ID);
    void deleteRequest(const QString &ID);

public slots:


private slots:
    void onReadyRead();

};

#endif // SERVERSOCKET_H
