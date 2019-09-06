#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QMainWindow>

namespace Ui {
class SubWindow;
}

class SubWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SubWindow(QWidget *parent = 0);
    ~SubWindow();

public slots:
    void slot1();
    void slot2();
    void slot3();
private:
    Ui::SubWindow *ui;
    QWidget *parent;
    int login;
    int reg;
    int ser;
    QString RoomNum;
    QString patInf;
};

#endif // SUBWINDOW_H
