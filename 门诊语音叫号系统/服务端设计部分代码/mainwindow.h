#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGui>
#include"subwindow.h"
#include"sub2window.h"
#include"sql3.h"
#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    SubWindow* sub;
    sub2Window* sub2;

public:
    sqlOperator *op;
    QTcpServer* server;
    QTcpSocket* socket;

public slots:
    void onNewconnect();
    void slot1();
    void slot2();
    void slot3();
    void slot4();

};

#endif // MAINWINDOW_H
