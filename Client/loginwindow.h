#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {class LoginWindow;}

class LoginWindow : public QWidget{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void displayError(const QString &error);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    bool validate_email(const QString &email);
    bool validate_pwd(const QString &password);

    void keep_me();
private:
    Ui::LoginWindow *ui;
    QPoint m_startPoint;

signals:
    void attemptSignup(const QString &email,const QString &username,const QString &password);
    void attemptLogin(const QString &username,const QString &password);

public slots:
    void loggedIn();

private slots:
    void on_login_clicked();
    void on_goto_signup_clicked();
    void on_signup_clicked();
    void on_back_clicked();
};

#endif // LOGINWINDOW_H
