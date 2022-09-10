#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>
#include <QGraphicsEffect>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->email->hide();
    ui->email_logo->hide();
    ui->signup->hide();
    ui->back->hide();
    ui->pwd_confirmation->hide();
    ui->reconfirm_logo->hide();
    keep_me();

    // alignment adjustment
    ui->username->setAlignment(Qt::AlignCenter);
    ui->password->setAlignment(Qt::AlignCenter);
    ui->error->setAlignment(Qt::AlignCenter);
    ui->email->setAlignment(Qt::AlignCenter);
    ui->pwd_confirmation->setAlignment(Qt::AlignCenter);

    //title bar buttons
    connect(ui->close_butt, SIGNAL(clicked()), SLOT(close()));
    connect(ui->minimize_butt, SIGNAL(clicked()), SLOT(showMinimized()));

    // changing placeholder color
    QPalette palette = (ui->username)->palette();
    palette.setColor(QPalette::PlaceholderText, QColor(198, 193, 193, 255));
    (ui->username)->setPalette(palette);

    QPalette palette1 = (ui->password)->palette();
    palette1.setColor(QPalette::PlaceholderText, QColor(198, 193, 193, 255));
    (ui->password)->setPalette(palette1);

    QPalette palette2 = (ui->email)->palette();
    palette2.setColor(QPalette::PlaceholderText, QColor(198, 193, 193, 255));
    (ui->email)->setPalette(palette2);

    QPalette palette3 = (ui->email)->palette();
    palette3.setColor(QPalette::PlaceholderText, QColor(198, 193, 193, 255));
    (ui->pwd_confirmation)->setPalette(palette3);

    // adding shadow effect
    QGraphicsDropShadowEffect *pLabelTextShadowEffect = new QGraphicsDropShadowEffect(ui->WELCOME);
    pLabelTextShadowEffect->setColor(QColor(0,0,0,120));
    pLabelTextShadowEffect->setBlurRadius(15);
    pLabelTextShadowEffect->setOffset(0, 3);
    (ui->WELCOME)->setGraphicsEffect(pLabelTextShadowEffect );

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor(QColor(0,0,0,120));
    shadowEffect->setBlurRadius(25);
    shadowEffect->setOffset(0, 3);
    (ui->username)->setGraphicsEffect(shadowEffect);

    QGraphicsDropShadowEffect* shadowEffect1 = new QGraphicsDropShadowEffect(this);
    shadowEffect1->setColor(QColor(0,0,0,120));
    shadowEffect1->setBlurRadius(25);
    shadowEffect1->setOffset(0, 3);
    (ui->password)->setGraphicsEffect(shadowEffect1);

    QGraphicsDropShadowEffect* shadowEffect2 = new QGraphicsDropShadowEffect(this);
    shadowEffect2->setColor(QColor(0,0,0,120));
    shadowEffect2->setBlurRadius(25);
    shadowEffect2->setOffset(0, 3);
    (ui->login)->setGraphicsEffect(shadowEffect2);

    QGraphicsDropShadowEffect* shadowEffect3 = new QGraphicsDropShadowEffect(this);
    shadowEffect3->setColor(QColor(0,0,0,120));
    shadowEffect3->setBlurRadius(25);
    shadowEffect3->setOffset(0, 3);
    (ui->email)->setGraphicsEffect(shadowEffect3);

    QGraphicsDropShadowEffect* shadowEffect4 = new QGraphicsDropShadowEffect(this);
    shadowEffect4->setColor(QColor(0,0,0,120));
    shadowEffect4->setBlurRadius(25);
    shadowEffect4->setOffset(0, 3);
    (ui->pwd_confirmation)->setGraphicsEffect(shadowEffect4);

    QGraphicsDropShadowEffect* shadowEffect5 = new QGraphicsDropShadowEffect(this);
    shadowEffect5->setColor(QColor(0,0,0,120));
    shadowEffect5->setBlurRadius(25);
    shadowEffect5->setOffset(0, 3);
    (ui->signup)->setGraphicsEffect(shadowEffect5);

    QGraphicsOpacityEffect * opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.9);
    (ui->background)->setGraphicsEffect(opacity);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
}

LoginWindow::~LoginWindow(){
    delete ui;
}


bool LoginWindow::validate_email(const QString &email){
    //ADD STUFF HERE
    if (email.contains("@")==false){
        return false;
    }
    return true;
}

bool LoginWindow::validate_pwd(const QString &password){
    // pwd policy:
    // - password length must be between 8-16
    // - password must contains at least 1 capitalized letter and 1 non-capitalized letter
    // - other symbols (such as _,!?) are allowed.

    QRegularExpression regPsw("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[\\s\\S]{8,16}$");
         if(regPsw.match(password).hasMatch()){
                return true;
         }else {
//             qDebug()<<password;
//             qDebug()<<"does not allow\n";
             return false;
         }
    return true;
}

void LoginWindow::on_signup_clicked(){
    ui->error->setText("");
    QString email = ui->email->text();
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString confirm = ui->pwd_confirmation->text();
    if (!validate_email(email)){
        ui->error->setText("Email is not valid");
    }else if(username==""){
        ui->error->setText("Username is empty");
    }else if (!validate_pwd(password)){
        ui->error->setText("Password is not valid");
    }else if (password!=confirm){
        ui->error->setText("Password did not match");
    }else{
        emit attemptSignup(email,username,password);
    }
}

void LoginWindow::on_login_clicked(){
    ui->error->setText("");
    QString username = ui->username->text();
    QString password = ui->password->text();
    emit attemptLogin(username,password);
}

void LoginWindow::loggedIn(){
    if (ui->Keep_me->isChecked()){
        QJsonObject keep_json;
        keep_json.insert("username",ui->username->text());
        keep_json.insert("password",ui->password->text());
        keep_json.insert("keep_me",true);
        QJsonDocument data;
        data.setObject(keep_json);
        //save to json file
        QFile file("../Client/keep_me.json");
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(data.toJson());
        file.close();
    }else{
        QJsonObject keep_json;
        keep_json.insert("username",ui->username->text());
        keep_json.insert("password",ui->password->text());
        keep_json.insert("keep_me",false);
        QJsonDocument data;
        data.setObject(keep_json);
        //save to json file
        QFile file("../Client/keep_me.json");
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(data.toJson());
        file.close();
    }
}

void LoginWindow::keep_me(){
    QFile file("../Client/keep_me.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument data = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject keep_json = data.object();
    ui->Keep_me->setChecked(keep_json.value("keep_me").toBool());
    if (keep_json.value("keep_me").toBool()){
        ui->username->setText(keep_json.value("username").toString());
        ui->password->setText(keep_json.value("password").toString());
    }
}


void LoginWindow::on_goto_signup_clicked(){
    ui->error->setText("");
    ui->username->setText("");
    ui->password->setText("");
    ui->login->hide();
    ui->Keep_me->hide();
    ui->WELCOME->hide();
    ui->forgot_password->hide();
    ui->goto_signup->hide();
    ui->signup->show();
    ui->back->show();
    ui->email->show();
    ui->email_logo->show();
    ui->pwd_confirmation->show();
    ui->reconfirm_logo->show();
    ui->username->setPlaceholderText("Enter Username");


}

void LoginWindow::on_back_clicked()
{
    ui->error->setText("");
    ui->username->setText("");
    ui->password->setText("");
    ui->login->show();
    ui->goto_signup->show();
    ui->signup->hide();
    ui->back->hide();
    ui->email->hide();
    ui->email_logo->hide();
    ui->WELCOME->show();
    ui->Keep_me->show();
    ui->forgot_password->show();
    ui->pwd_confirmation->hide();
    ui->reconfirm_logo->hide();
    ui->username->setPlaceholderText("Enter Username/ Email");

    keep_me();
}

void LoginWindow::displayError(const QString &error){
    ui->error->setText(error);
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_startPoint = frameGeometry().topLeft() - event->globalPos();
        }
    }

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() + m_startPoint);
}
