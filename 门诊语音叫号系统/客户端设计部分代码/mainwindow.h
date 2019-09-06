#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sounddevice.h>
#include <QTcpSocket>
#include "log.h"
#include "roll.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void start(QByteArray byteArray);
	void buzz();
	void led();
protected:
    void changeEvent(QEvent *e);
public slots:
    void on_loginBt_clicked();
    void on_buttun();
    void reshow();
    void on_roll_clicked();
    void quit();
    void start();

    void pause();
    void stop();

    void readData();

public :
    char buffer[1024];

private:
    Ui::MainWindow *ui;
    class log *win;
    class roll *ro;
    SoundDevice *device;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
