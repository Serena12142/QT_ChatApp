#include "loadingwindow.h"
#include "ui_loadingwindow.h"
#include <QGraphicsOpacityEffect>

LoadingWindow::LoadingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingWindow)
{
    ui->setupUi(this);
    QPalette palette = ui->progressBar->palette();
    palette.setColor(QPalette::Text, QColor(255,255,255,255));
    palette.setColor(QPalette::HighlightedText, QColor(125,163,253,255));
    ui->progressBar->setPalette(palette);
    //title bar buttons
    connect(ui->close_bu, SIGNAL(clicked()), SLOT(close()));
    connect(ui->minimize_bu, SIGNAL(clicked()), SLOT(showMinimized()));

    QGraphicsOpacityEffect * opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.9);
    (ui->background)->setGraphicsEffect(opacity);


    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

}

LoadingWindow::~LoadingWindow(){
    delete ui;
}
