/********************************************************************************
** Form generated from reading UI file 'loadingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGWINDOW_H
#define UI_LOADINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingWindow
{
public:
    QProgressBar *progressBar;
    QLabel *background;
    QPushButton *close_bu;
    QPushButton *minimize_bu;
    QLabel *label;

    void setupUi(QWidget *LoadingWindow)
    {
        if (LoadingWindow->objectName().isEmpty())
            LoadingWindow->setObjectName(QString::fromUtf8("LoadingWindow"));
        LoadingWindow->resize(400, 275);
        progressBar = new QProgressBar(LoadingWindow);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(115, 203, 171, 23));
        QFont font;
        font.setFamily(QString::fromUtf8("Poppins"));
        font.setBold(true);
        progressBar->setFont(font);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar:horizontal {\n"
"border: 2px solid #FFFFFF;\n"
"border-radius: 3px;\n"
"background: #7DA3FD;\n"
"padding: 1px;\n"
"text-align: center;\n"
"}\n"
"QProgressBar::chunk:horizontal {\n"
"background: #FFFFFF;\n"
"}"));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);
        background = new QLabel(LoadingWindow);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(0, 0, 400, 275));
        background->setStyleSheet(QString::fromUtf8("QLabel#background{\n"
"border-radius: 10px;\n"
"background: #7DA3FD;\n"
"border: 3px solid;\n"
"border-color: #DBD9D9;\n"
"\n"
"}\n"
"\n"
""));
        close_bu = new QPushButton(LoadingWindow);
        close_bu->setObjectName(QString::fromUtf8("close_bu"));
        close_bu->setGeometry(QRect(365, 10, 24, 24));
        close_bu->setFont(font);
        close_bu->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 1px solid #707070;\n"
"border-radius: 10px;\n"
"background:#DD6243;\n"
"color: #707070;\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid #E8907A;\n"
"border-radius: 10px;\n"
"background:#E8907A;\n"
"color: #FFFBDB;\n"
"}"));
        minimize_bu = new QPushButton(LoadingWindow);
        minimize_bu->setObjectName(QString::fromUtf8("minimize_bu"));
        minimize_bu->setGeometry(QRect(334, 10, 24, 24));
        minimize_bu->setFont(font);
        minimize_bu->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 1px solid #707070;\n"
"border-radius: 10px;\n"
"background:#FFFBDB;\n"
"color: #707070;\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid #535249;\n"
"border-radius: 10px;\n"
"background:#535249;\n"
"color: #FFFBDB;\n"
"}"));
        label = new QLabel(LoadingWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 180, 81, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Poppins"));
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:#FFFFFF;\n"
"}"));
        background->raise();
        close_bu->raise();
        minimize_bu->raise();
        progressBar->raise();
        label->raise();

        retranslateUi(LoadingWindow);

        QMetaObject::connectSlotsByName(LoadingWindow);
    } // setupUi

    void retranslateUi(QWidget *LoadingWindow)
    {
        LoadingWindow->setWindowTitle(QCoreApplication::translate("LoadingWindow", "Form", nullptr));
        background->setText(QString());
        close_bu->setText(QCoreApplication::translate("LoadingWindow", "x", nullptr));
        minimize_bu->setText(QCoreApplication::translate("LoadingWindow", "-", nullptr));
        label->setText(QCoreApplication::translate("LoadingWindow", "LOADING", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadingWindow: public Ui_LoadingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGWINDOW_H
