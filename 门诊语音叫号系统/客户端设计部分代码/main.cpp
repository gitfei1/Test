#include <QApplication>
#include "mainwindow.h"
//#include <QTextCodec>
#include<QtCore/QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *code = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    MainWindow w;


    w.show();
    
    return a.exec();
}
