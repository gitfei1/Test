#include <QtGui/QApplication>
#include<iostream>
#include "mainwindow.h"
#include<QTextCodec>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    MainWindow w;
    w.show();
    //qDebug("abc");
    return a.exec();
}
