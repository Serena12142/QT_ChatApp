#ifndef SERVER_H
#define SERVER_H
#include "serversocket.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>

class Server : public QObject{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
private:
    QTcpServer* server;
    QVector<ServerSocket*> clients;
    QHash<QString,QHash<QString,QString>> all_users;
    QHash<QString,QString> registered_usernames;
    QHash<QString,QString> registered_emails;
    QVector<QString> active_users;

    QString new_ID();
    void remove_user(const QString &ID);

signals:

private slots:
    void newConnection();
    void userConnectionError(ServerSocket* client, QAbstractSocket::SocketError socketError);
    void signout(const QString &ID);

    void attemptLogin(ServerSocket* client, const QString &username, const QString &password);
    void attemptSignup(ServerSocket* client, const QString &email, const QString &username, const QString &password);
    void changeProfile(ServerSocket* client, QHash<QString,QString> profile);

    void messageReceived(ServerSocket* client, QHash<QString,QString> &message);

    void getRequests(ServerSocket* client);
    void sendRequest(ServerSocket *client, const QString &receiver_ID);
    void makeFriend(ServerSocket *client, const QString &ID2);
    void deleteRequest(ServerSocket *client, const QString &ID2);
};

#endif // SERVER_H
