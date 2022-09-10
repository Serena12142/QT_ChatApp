#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include "loadingwindow.h"
#include "loginwindow.h"
#include "client.h"

namespace Ui {class MainWindow;}

class MainWindow : public QWidget{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoadingWindow* loading;
    LoginWindow* login;
    Client* client;
    QPoint m_startPoint;

    //chat
    void display_message(QHash<QString,QString> message);
    void modify_message(int index, QHash<QString,QString> message);
    QString cur_time();

    // Added for resizing window
    QPoint mpos; //For dragging, relative mouse position to upper left
    QPoint global_mpos; //For resizing, global mouse position at mouse click
    QPoint rs_mpos; //for resizing
    int storeWidth; //fix window size at mouseclick for resizing
    int storeHeight;

    //utility functions
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void remove(QLayout* layout);
    QPixmap PixmapToRound(const QPixmap &src, int radius);
    int compareQdatetime (const QString id_1, const QString id_2);

    //requests
    void display_request(QHash<QString,QString> request, int match);


signals:

private slots:
    //connect
    void connected();
    void serverError(QAbstractSocket::SocketError socketError);

    //login
    void loginError(const QString &reason);
    void loggedIn();
    void startApplication();
    void on_signout_clicked();
    //profile
    void profileChanged();
    void profileError(const QString &reason);
    void on_settingbutton_clicked();
    void on_changeProfile_clicked();
    void on_changeprofilepic_clicked();

    //chat
    void on_send_clicked(); //send button
    void on_user_list_clicked(const QModelIndex &index);
    void on_info_butt_clicked();
    void display_friend_profile(const QString& ID);
    void on_profile_back_clicked(); //back to chat buttonn
    void messageReceived(QHash<QString,QString> &message);

    //requests
    void requestsReceived(QVector<QHash<QString,QString>> requests, int match);
    void add_friend(QPushButton* add);
    void delete_friend(QPushButton* del);
    void generateWelcomeMessage(const QString &ID);

    //ui
    void on_dictionary_2_clicked();
    void on_new_conversation_clicked();
    void on_maximize_butt_clicked();
    void on_minimize_butt_clicked();
    void msg_customContextMenuRequested(const QPoint &);
    void delete_msg();
    void copy_msg();
    void transalte_msg();
    void debug_msg();
    void on_quote_close_butt_clicked();
//    void on_tabWidget_currentChanged(int index);
};


#endif // MAINWINDOW_H
