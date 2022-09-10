#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QWidget>

namespace Ui {class LoadingWindow;}

class LoadingWindow : public QWidget{
    Q_OBJECT

public:
    explicit LoadingWindow(QWidget *parent = nullptr);
    ~LoadingWindow();
private:
    Ui::LoadingWindow *ui;
};

#endif // LOADINGWINDOW_H
