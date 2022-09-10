#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStyledItemDelegate>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>
#include <QSizePolicy>
#include <algorithm>
#include <QBitMap>
#include <QMenu>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    loading(new LoadingWindow()),
    login(new LoginWindow()),
    client(new Client(this))
{
    //connect to server
    connect(client,&Client::connected, this,&MainWindow::connected);
    connect(client,&Client::serverError, this,&MainWindow::serverError);
    //login
    connect(login,&LoginWindow::attemptLogin, client,&Client::attemptLogin);
    connect(login,&LoginWindow::attemptSignup, client,&Client::attemptSignup);
    connect(client,&Client::loggedIn, this,&MainWindow::loggedIn);
    connect(client,&Client::loggedIn, login,&LoginWindow::loggedIn);
    connect(client,&Client::loginError, this,&MainWindow::loginError);
    //profile
    connect(client,&Client::informationReceived, this,&MainWindow::startApplication);
    connect(client,&Client::profileChanged, this,&MainWindow::profileChanged);
    connect(client,&Client::profileError, this,&MainWindow::profileError);
    //message
    connect(client,&Client::messageReceived, this,&MainWindow::messageReceived);
    //matches
    connect(client,&Client::requestsReceived, this,&MainWindow::requestsReceived);
    connect(client,&Client::getWelcomeMessage, this,&MainWindow::generateWelcomeMessage);
    connect(client,&Client::newFriend, this,&MainWindow::startApplication);

    //initialization
    ui->setupUi(this);
    this->hide();
    login->hide();
    loading->show();
    ui->dic_widget->hide();
    //title bar buttons
    connect(ui->close_butt, SIGNAL(clicked()), SLOT(close()));
    connect(ui->minimize_butt, SIGNAL(clicked()), SLOT(showMinimized()));

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor(QColor(0,0,0,120));
    shadowEffect->setBlurRadius(25);
    shadowEffect->setOffset(3, 3);
    (ui->user_pic)->setGraphicsEffect(shadowEffect);

    QGraphicsDropShadowEffect* shadowEffect1 = new QGraphicsDropShadowEffect(this);
    shadowEffect1->setColor(QColor(0,0,0,120));
    shadowEffect1->setBlurRadius(25);
    shadowEffect1->setOffset(0, 3);
    (ui->new_conversation)->setGraphicsEffect(shadowEffect1);

    QGraphicsDropShadowEffect* shadowEffect2 = new QGraphicsDropShadowEffect(this);
    shadowEffect2->setColor(QColor(0,0,0,120));
    shadowEffect2->setBlurRadius(25);
    shadowEffect2->setOffset(0, 3);
    (ui->dictionary_2)->setGraphicsEffect(shadowEffect2);

    QGraphicsDropShadowEffect* shadowEffect3 = new QGraphicsDropShadowEffect(this);
    shadowEffect3->setColor(QColor(0,0,0,120));
    shadowEffect3->setBlurRadius(25);
    shadowEffect3->setOffset(0, 3);
    (ui->widget)->setGraphicsEffect(shadowEffect3);

    QGraphicsDropShadowEffect* shadowEffect4 = new QGraphicsDropShadowEffect(this);
    shadowEffect4->setColor(QColor(0,0,0,120));
    shadowEffect4->setBlurRadius(25);
    shadowEffect4->setOffset(0, 3);
    (ui->stackedWidget)->setGraphicsEffect(shadowEffect4);

    QPalette palette3 = (ui->username_enter)->palette();
    palette3.setColor(QPalette::PlaceholderText, QColor(255,255,255,255));
    (ui->username_enter)->setPalette(palette3);

    QPalette palette4 = (ui->textEdit)->palette();
    palette4.setColor(QPalette::PlaceholderText, QColor(255,255,255,255));
    (ui->textEdit)->setPalette(palette4);

    QPalette palette5 = (ui->enter_email)->palette();
    palette5.setColor(QPalette::PlaceholderText, QColor(255,255,255,255));
    (ui->enter_email)->setPalette(palette5);

    ui->pro_comboBox->view()->window()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    ui->pro_comboBox->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    ui->language_1st_com->view()->window()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    ui->language_1st_com->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    ui->language_2nd_com->view()->window()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    ui->language_2nd_com->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    ui->language_3rd_com->view()->window()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    ui->language_3rd_com->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
//    QString path = client->profile["profile_pic_path"];
//    QString path = "sgfkber2";
//    QPixmap source(path);
//    QPixmap scaled = PixmapToRound(source,65);
//    ui->displayprofile->setPixmap(scaled);
//    QPixmap scaled_1 = PixmapToRound(source,50);
//    ui->user_pic->setPixmap(scaled_1);
    client->connectToServer();

    ui->stackedWidget->setCurrentWidget(ui->chat);
    ui->quote_widget->hide();
}

MainWindow::~MainWindow()
{
    delete loading;
    delete login;
    delete ui;
}

void MainWindow::startApplication(){
    loading->hide();
    this->show();
    //initialize friend list
    //  get IDs sorted by most recent messsage
    QList<QString> friend_IDs = client->friend_messages.keys();

    std::sort(friend_IDs.begin(), friend_IDs.end(), [this](const QString id_1, const QString id_2)->bool {
        QHash<QString,QString> message_1 = client->friend_messages[id_1].at(client->friend_messages[id_1].count()-1);
        QHash<QString,QString> message_2 = client->friend_messages[id_2].at(client->friend_messages[id_2].count()-1);
        QDateTime time_1 = QDateTime::fromString(message_1["time"],"dd-MM-yyyy hh:mm");
        QDateTime time_2 = QDateTime::fromString(message_2["time"],"dd-MM-yyyy hh:mm");
//        qDebug()<<time_1<<": this is time_1";
//        qDebug()<<time_2<<": this is time_2";
        return time_1 > time_2;
    });

    // display own name
    QString my_name = client->profile["username"];
    ui->username->setText(my_name);

    //  display friends
    ui->user_list->clear();
    for(const QString& ID: friend_IDs){
        QListWidgetItem *user = new QListWidgetItem;
        user->setData(Qt::UserRole, ID);
        user->setText(client->friend_profiles[ID]["username"]);
        user->setTextAlignment(Qt::AlignCenter);
        ui->user_list->addItem(user);
    }
    if (ui->user_list->count() > 0) {
        ui->user_list->setCurrentItem(ui->user_list->item(0));
        on_user_list_clicked(ui->user_list->currentIndex());
    }else{
        on_settingbutton_clicked();
    }
}

void MainWindow::display_friend_profile(const QString& friend_ID){
    ui->stackedWidget->setCurrentWidget(ui->chat_profile);
//    QString friend_ID=ui->past_request_list->currentIndex().data(Qt::UserRole).toString();
//    qDebug()<<friend_ID;
    QString my_friends_name = client->friend_profiles[friend_ID]["username"];
    ui->friend_name->setText(my_friends_name);

    QString intro = client->friend_profiles[friend_ID]["intro"];
    ui->intro_content->setText(intro);

    QString pronoun = client->friend_profiles[friend_ID]["pronoun"];
    ui->pronoun_content->setText(pronoun);

    ui->lan_1st_label->setText(client->friend_profiles[friend_ID]["language1"]);
    ui->lan_2nd_label->setText(client->friend_profiles[friend_ID]["language2"]);
    ui->lan_3rd_label->setText(client->friend_profiles[friend_ID]["language3"]);

}


void MainWindow::on_info_butt_clicked()
{
    QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
    display_friend_profile(friend_ID);
}

void MainWindow::on_user_list_clicked(const QModelIndex &index)
{
    //initiallize chat
    ui->stackedWidget->setCurrentWidget(ui->chat);
    //  username
    QString friendname = index.data(Qt::DisplayRole).toString();
    remove(ui->layout_scroll);
    ui->layout_scroll->addStretch(0);
    ui->chat_username->setText(friendname);
    // chat messages
    for(const QHash<QString,QString> &message:client->friend_messages[index.data(Qt::UserRole).toString()]){
        display_message(message);
    }
}

void MainWindow::generateWelcomeMessage(const QString& ID){
    QHash<QString,QString> message;
    QString html_code = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:\'Poppins\'; font-size:12pt; font-weight:400; font-style:normal;\"><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br />hi</p></body></html>";
    message["content"]=html_code;
    message["sender"]=client->ID;
    message["receiver"]=ID;
    message["time"]=cur_time();
    message["is_quote"] = "-1";
    client->friend_messages[ID].push_back(message);
    client->sendMessage(message);
}

void MainWindow::on_send_clicked()
{
    QString html_code = ui->chat_input->toHtml();
    QString empty_text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:\'Poppins\'; font-size:12pt; font-weight:400; font-style:normal;\"><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>";

    if(ui->chat_input->toHtml()== empty_text){
        return;
    }

    QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
    QString quote_or_not;
//    //create message
    if(ui->quote_widget->isHidden()){
        quote_or_not = "-1"; }
    else{
        // change here for the quoting reference
        quote_or_not = "1";
    }

    QHash<QString,QString> message;
    message["content"]=html_code;
    message["sender"]=client->ID;
    message["receiver"]=friend_ID;
    message["time"]=cur_time();
    message["is_quote"] = quote_or_not;

    ui->chat_input->setHtml(empty_text);

    display_message(message);
    client->friend_messages[friend_ID].push_back(message);
    client->sendMessage(message);

    if(ui->user_list->currentRow()!=0){
    QListWidgetItem *latest_user = ui->user_list->takeItem(ui->user_list->currentRow());
    ui->user_list->insertItem(0,latest_user);
    ui->user_list->setCurrentItem(ui->user_list->item(0));
    }

    if(!ui->quote_widget->isHidden()){
        ui->quote_widget->hide();
    }

}

void MainWindow::messageReceived(QHash<QString,QString> &message){
    if(ui->stackedWidget->currentWidget()==ui->chat){
        QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
//        qDebug()<<friend_ID;
        display_message(message);
        QString ID = message["sender"];
//        qDebug()<<ui->user_list->row(ui->user_list->findItems(client->friend_profiles[ID]["username"],Qt::MatchExactly)[0]);
        QListWidgetItem *latest_user = ui->user_list->takeItem(ui->user_list->row(ui->user_list->findItems(client->friend_profiles[ID]["username"],Qt::MatchExactly)[0]));
        ui->user_list->insertItem(0,latest_user);
        ui->user_list->setCurrentItem(ui->user_list->item(0));
    }
}

void MainWindow::add_friend(QPushButton* add){
    QString ID=add->property("ID").toString();
    if(ui->matching_tab->currentIndex()==0){
        //accept
        client->acceptRequest(ID);
    }else{
        //send request
        client->sendRequest(ID);
    }
    delete_friend(add);
}

void MainWindow::delete_friend(QPushButton* del){
    if(ui->matching_tab->currentIndex()==0){
        for(int i = 0; i < ui->past_request_list->count(); ++i)
        {
            if(ui->past_request_list->item(i)->data(Qt::UserRole).toString()==del->property("ID")){
                ui->past_request_list->takeItem(i);
                client->deleteRequest(del->property("ID").toString());
                break;
            }
        }
    }
    /*
    else{
        for(int i = 0; i < ui->new_request_list->count(); ++i)
        {
            if(ui->new_request_list->item(i)->data(Qt::UserRole).toString()==del->property("ID")){
                ui->new_request_list->takeItem(i);
            }

        }
    }*/
}

void MainWindow::display_request(QHash<QString,QString> request, int match){
    // somehow find the username from the given id parameter (this id here needs to carry other useful
    // info to be later displayed in the info page)
    QString user_ID=request["ID"];

    // create a new listwidget item(not including styling)
    QListWidgetItem *user = new QListWidgetItem;
    user->setData(Qt::UserRole,user_ID);
    QWidget * user_container = new QWidget;
    QPushButton * username = new QPushButton(this);
    username->setProperty("ID",user_ID);
    connect(username,&QPushButton::clicked,this,
            std::bind(&MainWindow::display_friend_profile, this,  username->property("ID").toString()));


    username->setStyleSheet("QPushButton{color: rgb(80, 103, 156);"
                            "padding-left:15px;"
                            "background-color:rgba(0,0,0,0);}"
                            "QPushButton:hover{color:white;}");
    QFont name("Poppins", 13);
    QFont butt("Poppins",10);
    //name.setBold(true);
    username->setFont(name);
    username->setText(request["username"]);

    QPushButton * add = new QPushButton("Add");
    add->setProperty("ID",user_ID);
    //add->setProperty("username",request["username"]);
    connect(add,&QPushButton::clicked,this,
            std::bind(&MainWindow::add_friend, this, add));

    QPushButton * del = new QPushButton("Delete");
    del->setProperty("ID",user_ID);
    //del->setProperty("username",request["username"]);
    connect(del,&QPushButton::clicked,this,
            std::bind(&MainWindow::delete_friend, this, del));

    del->setMinimumSize(50,24);
    del->setFont(butt);
    add->setMinimumSize(50,24);
    add->setFont(butt);
    QString stylesheet_del = "QPushButton{"
                            "background-color: rgb(81, 111, 194);"
                            "border-radius: 10px;"
                            "color: #E1EAFE;"
                            "padding-left:15px;padding-right:15px;"
                            "}"
                            "QPushButton:hover{"
                            "border: 1px solid rgba(0,0,0,0);"
                            "border-radius: 10px;"
                            "background:#E8907A;"
                            "color: #FFFBDB;"
                            "}";
    QString stylesheet_add = "QPushButton{"
                            "background-color: rgb(81, 111, 194);"
                            "border-radius: 10px;"
                            "color: #E1EAFE;"
                            "padding-left:15px;padding-right:15px;"
                            "}"
                            "QPushButton:hover{"
                            "border: 1px solid rgba(0,0,0,0);"
                            "border-radius: 10px;"
                            "background:#d4ff8e;"
                            "color: #4c5b33;"
                            "}";
    del->setStyleSheet(stylesheet_del);
    add->setStyleSheet(stylesheet_add);

    QHBoxLayout * layout = new QHBoxLayout(user_container);
    layout->addWidget(username);
    layout->addStretch(0);
    layout->addWidget(add);
    //layout->addWidget(del);

    if (match==0){
        ui->past_request_list->addItem(user);
        ui->past_request_list->setItemWidget(user,user_container);
        layout->addWidget(del);
    }else{
        ui->new_request_list->addItem(user);
        ui->new_request_list->setItemWidget(user,user_container);
    }
}

void MainWindow::requestsReceived(QVector<QHash<QString,QString>> requests, int match){
    if (match==1){
        ui->new_request_list->clear();
    }else{
        ui->past_request_list->clear();
    }
    //could sort here by time ***
    for(const QHash<QString,QString>& request:requests){
        display_request(request, match);
    }
}

void MainWindow::on_new_conversation_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->matching);
    //some kind of loading screen?

    // send message to server
    client->getRequests();
}

void MainWindow::display_message(QHash<QString,QString> message){
    // get info from message object
    QString content = message["content"];
    bool sender = message["sender"]==client->ID;
    QString sent_time = message["time"];

    //display on screen
    QWidget *window = new QWidget;
    QLabel *text_msg = new QLabel(this);
    text_msg->setText(content);
    text_msg->setWordWrap(true);
    text_msg->setMaximumWidth(500);
    text_msg->setMinimumWidth(50);
    text_msg->setMinimumHeight(50);
    text_msg->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
    QFont f("Poppins", 11);
    QFont t("Poppins", 9);
    text_msg->setFont(f);
    QHBoxLayout *layout = new QHBoxLayout(window);
    if (sender){
        text_msg->setStyleSheet("QLabel{background-color:#6781C3;"
                                " color:#EBF0FF;"
                                " border:1px solid rgba(0,0,0,0);"
                                " border-radius:25px;"
                                " padding-left:15px;"
                                " padding-right:15px;"
                                " padding-top:15px;"
                                " padding-bottom:15px;}");
        layout->addStretch(0);
        layout->addWidget(text_msg);
    }else{
        text_msg->setStyleSheet("QLabel{background-color:#EBF0FF;"
                                " color:#6781C3;"
                                " border:1px solid rgba(0,0,0,0);"
                                " border-radius:25px;"
                                " padding-left:15px;"
                                " padding-right:15px;"
                                " padding-top:15px;"
                                " padding-bottom:15px;}");
        layout->addWidget(text_msg);
        layout->addStretch(0);
    }
    QWidget *complex = new QWidget;
    QVBoxLayout *H_layout = new QVBoxLayout(complex);
    H_layout->addWidget(window);

    QWidget *subblock = new QWidget;
    QHBoxLayout *subblock_layout = new QHBoxLayout(subblock);
    QLabel *time = new QLabel(this);


    QPushButton *Q = new QPushButton();
    Q->setText("Q");
    QFont q_font("Poppins", 8);
    Q->setFont(q_font);
    Q->setStyleSheet("QPushButton{"
                    "border: 1px solid #E8907A;"
                    "border-radius: 9px;"
                    "background:rgb(232, 177, 163);"
                    "color: #FFFBDB;"
                    "}"
                    "QPushButton:hover{"
                    "border: 1px solid #FFFBDB;"
                    "border-radius: 9px;"
                    "background:rgb(221, 148, 139);"
                    "color: #FFFBDB;"
                    "}");
    Q->setMinimumWidth(18);
    Q->setMaximumWidth(18);

    time->setText(sent_time);
    if (sender){
        subblock_layout->addStretch(0);
        time->setAlignment(Qt::AlignRight);
        subblock_layout->addWidget(Q);
        subblock_layout->addWidget(time);
    }else{
//        time->setAlignment(Qt::AlignRight);
        subblock_layout->addWidget(time);
        subblock_layout->addWidget(Q);
        subblock_layout->addStretch(0);
    }
    time->setFont(t);
    H_layout->addWidget(subblock);
    if(message["is_quote"]=="-1"){
        Q->hide();
    }
    int count_num = ui->chat_content->layout()->count();
    ui->layout_scroll->insertWidget(count_num-1,complex);

    complex->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(complex,SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(msg_customContextMenuRequested(const QPoint&)));
}

void MainWindow::msg_customContextMenuRequested(const QPoint &)
{

    QWidget * new_w = qobject_cast<QWidget *>(this->sender());
    int pos = ui->layout_scroll->indexOf(new_w);

    QMenu *pMenu = new QMenu(this);

    QAction *pcopy = new QAction(tr("Copy message"), this);
    QAction *pquote = new QAction(tr("Quote message"), this);
    QAction *ptranslate = new QAction(tr("Translate message"), this);
    QAction *pdelete = new QAction(tr("Delete message"),this);

    pcopy->setData(pos);
    pquote->setData(pos);
    ptranslate->setData(pos);
    pdelete->setData(pos);

    pMenu->addAction(pcopy);
    pMenu->addAction(pquote);
    pMenu->addAction(ptranslate);
    pMenu->addAction(pdelete);

    connect(ptranslate, SIGNAL(triggered()), SLOT(transalte_msg()));
    connect(pcopy, SIGNAL(triggered()), SLOT(copy_msg()));
    connect(pquote, SIGNAL(triggered()), SLOT(debug_msg()));
    connect(pdelete, SIGNAL(triggered()), SLOT(delete_msg()));
    QString  menuStyle(
               "QMenu::item{"
               "background-color: rgb(157, 180, 237);"
               "color: rgb(255, 255, 255);"
               "font: 9pt 'Poppins';"
               "padding-top: 5px;"
               "padding-bottom: 5px;"
               "padding-left: 10px;"
               "padding-right: 10px;"
               "margin-left: 5px;"
               "margin-right: 5px;"
               "}"
               "QMenu{"
               "background-color:rgb(157, 180, 237);"
               "}"
               "QMenu::item:selected{"
               "background-color: rgba(100, 127, 194, 255);"
               "border-radius:10px;"
               "color: rgb(255, 255, 255);"
               "font: 9pt 'Poppins';"
               "}"
            );

     pMenu->setStyleSheet(menuStyle);

    // show menu
    pMenu->exec(cursor().pos());

    // free spaces in case two rc-menu bars appear
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

void MainWindow::debug_msg(){

    QAction *position = qobject_cast<QAction *>(this->sender());
    int index = position->data().toInt();

    QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
    QString msg = client->friend_messages[friend_ID].at(index)["content"];
    ui->quote_msg->setText(msg);
    ui->quote_widget->show();
}

void MainWindow::delete_msg(){
    QAction *position = qobject_cast<QAction *>(this->sender());

    int index = position->data().toInt();
    QLayoutItem* child;
    child = ui->layout_scroll->takeAt(index);
    if ( child->layout() != 0 ) {
        remove ( child->layout() );
    } else if ( child->widget() != 0 ) {
        delete child->widget();
    }
    delete child;
    // finish this function by deleting the according message in the server
    // or a better way might be adding a parameter (is_del:bool) in the message
    // json file so that we always have the root file in hand.
}

void MainWindow::transalte_msg(){
    QAction *position = qobject_cast<QAction *>(this->sender());
    int index = position->data().toInt();

    QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
    QString msg = client->friend_messages[friend_ID].at(index)["content"];
    on_dictionary_2_clicked();
    ui->dic_input->setText(msg);

}

void MainWindow::copy_msg(){
    QAction *position = qobject_cast<QAction *>(this->sender());
    int index = position->data().toInt();

    QString friend_ID=ui->user_list->currentIndex().data(Qt::UserRole).toString();
    QString msg = client->friend_messages[friend_ID].at(index)["content"];
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(msg);
}

void MainWindow::profileError(const QString &reason){
    ui->profileError->setText(reason);
}

void MainWindow::profileChanged(){
    ui->profileError->setText("Profile changed!");
}

void MainWindow::on_changeProfile_clicked(){
    if(ui->username_enter->text()==""){
        ui->profileError->setText("username is not empty");
    }else if(!login->validate_email(ui->enter_email->text())){
        ui->profileError->setText("Email is not valid");
    }else{
        client->profile["username"]=ui->username_enter->text();
        client->profile["email"]=ui->enter_email->text();
        client->profile["intro"]=ui->textEdit->toPlainText();
        client->profile["pronoun"]=ui->pro_comboBox->currentText();
        client->profile["language1"]=ui->language_1st_com->currentText();
        client->profile["language2"]=ui->language_2nd_com->currentText();
        client->profile["language3"]=ui->language_3rd_com->currentText();
        client->updateProfile();
    }
}

void MainWindow::loginError(const QString &reason){
    login->displayError(reason);
}

void MainWindow::loggedIn(){
    login->hide();
    loading->show();
}

void MainWindow::connected(){
    loading->hide();
    login->show();
}

void MainWindow::serverError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::critical(this, tr("Error"), tr("The host closed the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::TemporaryError:
        QMessageBox::warning(this, tr("Error"), tr("A temporary error occured"));
        return;
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
    }
    loading->hide();
    login->hide();
    this->close();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
        //commented out because we have other variables for resizing!
//        if (event->button() == Qt::LeftButton) {
//            m_startPoint = frameGeometry().topLeft() - event->globalPos();
//        }
        //From Qt Documentation:
        //Reason why pos() wasn't working is because the global
        //position at time of event may be very different
        //This is why the mpos = event->pos(); line before was
        //possibly causing jumping behavior

         if (event->button() == Qt::LeftButton){
             //Coordinates have been mapped such that the mouse position is relative to the
             //upper left of the main window
             mpos = event->globalPos() - frameGeometry().topLeft();

             //At the moment of mouse click, capture global position and
             //lock the size of window for resizing
             global_mpos = event->globalPos();
             storeWidth = this->width();
             storeHeight= this->height();

             event->accept();

         }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //this->move(event->globalPos() + m_startPoint);

    //mapped mouse relative to upper left of window
    rs_mpos=event->globalPos()-frameGeometry().topLeft();//general position tracker for resizing
    QTextStream out(stdout);

    //How much of the corner is considered a "resizing zone"
    //I was experiencing jumping behavior with rs_size is 10 so
    //I recommend rs_size=50
    int rs_size=50;

    //Big if statement checks if your mouse is in the upper left,
    //upper right, lower left, and lower right
    bool resizeZone = (abs(rs_mpos.x()) < rs_size && abs(rs_mpos.y()) < rs_size) ||
            (abs(rs_mpos.x()) > this->width()-rs_size && abs(rs_mpos.y()) <rs_size) ||
            (abs(rs_mpos.x()) < rs_size && abs(rs_mpos.y())> this->height()-rs_size) ||
            (abs(rs_mpos.x()) > this->width()-rs_size && abs(rs_mpos.y())> this->height()-rs_size);
    if (resizeZone){
        this->setCursor(Qt::SizeBDiagCursor);
         //Below for debugging
         /*
         out << rs_mpos.x() << " , " << rs_mpos.y() << "\n";
         out << "window: " << this->width() << " , " << this->height() << "\n";
         out << "globalpos: " << event->globalPos().x() << " , "
             << event->globalPos().y() << "\n";
        */

        //Use 2x2 matrix to adjust how much you are resizing and how much you
        //are moving. Since the default coordinates are relative to upper left
        //You cannot just have one way of resizing and moving the window.
        //It will depend on which corner you are referring to

        //adjXfac and adjYfac are for calculating the difference between your
        //current mouse position and where your mouse was when you clicked.
        //With respect to the upper left corner, moving your mouse to the right
        //is an increase in coordinates, moving mouse to the bottom is increase
        //etc.
        //However, with other corners this is not so and since I chose to subtract
        //This difference at the end for resizing, adjXfac and adjYfac should be
        //1 or -1 depending on whether moving the mouse in the x or y directions
        //increases or decreases the coordinates respectively.

        //transXfac transYfac is to move the window over. Resizing the window does not
        //automatically pull the window back toward your mouse. This is what
        //transfac is for (translate window in some direction). It will be either
        //0 or 1 depending on whether you need to translate in that direction.

        //Initiate matrix
        int adjXfac=0;
        int adjYfac=0;
        int transXfac=0;
        int transYfac=0;

        //Upper left corner section
        if ( (abs(rs_mpos.x()) < rs_size && abs(rs_mpos.y()) < rs_size)){
        this->setCursor(Qt::SizeFDiagCursor);



             //Upper left. No flipping of axis, no translating window
             adjXfac=1;
             adjYfac=1;

             transXfac=0;
             transYfac=0;



        }
        //Upper right corner section
        else if(abs(rs_mpos.x()) > this->width()-rs_size &&
                abs(rs_mpos.y()) <rs_size){
            this->setCursor(Qt::SizeBDiagCursor);


            //upper right. Flip displacements in mouse movement across x axis
            //and translate window left toward the mouse
            adjXfac=-1;
            adjYfac=1;

            transXfac = 1;
            transYfac =0;

         }

         //Lower left corner section
         else if(abs(rs_mpos.x()) < rs_size &&
                 abs(rs_mpos.y())> this->height()-rs_size){
            this->setCursor(Qt::SizeBDiagCursor);

            //lower left. Flip displacements in mouse movement across y axis
            //and translate window up toward mouse
            adjXfac=1;
            adjYfac=-1;

            transXfac=0;
            transYfac=1;


          }
          //Lower right corner section
          else if(abs(rs_mpos.x()) > this->width()-rs_size &&
                  abs(rs_mpos.y())> this->height()-rs_size){
              this->setCursor(Qt::SizeFDiagCursor);

             //lower right. Flip mouse displacements on both axis and
             //translate in both x and y direction left and up toward mouse.
             adjXfac=-1;
             adjYfac=-1;

             transXfac=1;
             transYfac=1;
            }

       if (event->buttons()==Qt::LeftButton ){

           //Calculation of displacement. adjXfac=1 means normal displacement
           //adjXfac=-1 means flip over axis
           int adjXdiff = adjXfac*(event->globalPos().x() - global_mpos.x());

           int adjYdiff = adjYfac*(event->globalPos().y() - global_mpos.y());

           //if transfac is 1 then movepoint of mouse is translated
           QPoint movePoint(mpos.x() - transXfac*adjXdiff, mpos.y()-transYfac*adjYdiff);
           move(event->globalPos()-movePoint);
           resize(storeWidth-adjXdiff, storeHeight-adjYdiff);

           event->accept();


         }

    }

     //in any move event if it is not in a resize region use the default cursor
     else{

         this->setCursor(Qt::ArrowCursor);


          //simple move section
          if (event->buttons()==Qt::LeftButton &&
              resizeZone==false){
              move(event->globalPos() - mpos);
              event->accept();
          }


     }

}

void MainWindow::on_settingbutton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Profile);

    ui->profileError->setText("");
    ui->username_enter->setText(client->profile["username"]);
    ui->enter_email->setText(client->profile["email"]);
    ui->textEdit->setText(client->profile["intro"]);
    ui->pro_comboBox->setCurrentIndex(ui->pro_comboBox->findText(client->profile["pronoun"]));
    ui->language_1st_com->setCurrentIndex(ui->language_1st_com->findText(client->profile["language1"]));
    ui->language_2nd_com->setCurrentIndex(ui->language_2nd_com->findText(client->profile["language2"]));
    ui->language_3rd_com->setCurrentIndex(ui->language_3rd_com->findText(client->profile["language3"]));
}

void MainWindow::on_dictionary_2_clicked()
{
//    ui->stackedWidget->setCurrentWidget(ui->dictionary);
    if(ui->dic_widget->isHidden()){
        ui->dic_widget->show();}
    else{
        ui->dic_widget->hide();
    }
}

void MainWindow::on_signout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chat);
    this->hide();
    login->show();
    login->keep_me();
    client->signout();
}

void MainWindow::on_maximize_butt_clicked()
{

    this->setWindowState(this->windowState()^Qt::WindowFullScreen);
}

void MainWindow::on_minimize_butt_clicked()
{
    this->setWindowState(this->windowState()^Qt::WindowMinimized);
}

void MainWindow::on_changeprofilepic_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *bmp *.gif)"));
    if(filename == ""){
        filename = ":/images/pic/profile.png";
        //filename = "/Users/robertren/Desktop/Google_SC/Client/pic/profile.png";
    }
    QPixmap source(filename);
    QPixmap scaled = PixmapToRound(source,65);
    ui->displayprofile->setPixmap(scaled);
    QPixmap scaled_1 = PixmapToRound(source,50);
    ui->user_pic->setPixmap(scaled_1);
    client->profile["profile_pic_path"] = filename;
    QImage img_to_save = scaled_1.toImage();
    QPixmap pixmap_to_change(":/profilepic/pic/profile.png");
    pixmap_to_change = source;
    pixmap_to_change.save("new_profile");
}

void MainWindow::on_profile_back_clicked()
{   if(ui->user_list->findItems(ui->friend_name->text(),Qt::MatchExactly).count()!=0){
       ui->stackedWidget->setCurrentWidget(ui->chat);
    }else{
        ui->stackedWidget->setCurrentWidget(ui->matching);
    }

//    qDebug()<<ui->user_list->findItems("hello",Qt::MatchExactly).count();
//    ui->stackedWidget->setCurrentWidget(ui->chat);
}

QString MainWindow::cur_time(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M",timeinfo);
    std::string str(buffer);
    QString time = QString::fromStdString(str);
    return time;
}

void MainWindow::remove(QLayout* layout)
{
    QLayoutItem* child;
    while ( layout->count() != 0 ) {
        child = layout->takeAt ( 0 );
        if ( child->layout() != 0 ) {
            remove ( child->layout() );
        } else if ( child->widget() != 0 ) {
            delete child->widget();
        }

        delete child;
    }
}

QPixmap MainWindow::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
    QSize size(8*radius, 8*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

void MainWindow::on_quote_close_butt_clicked()
{
    ui->quote_widget->hide();
}

