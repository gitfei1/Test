#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server  = new QTcpServer();
    socket = new QTcpSocket();
    server->listen(QHostAddress::Any,1100);
    connect(server,SIGNAL(newConnection()),this,SLOT(onNewconnect()));

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //.......
    //ui->textEdit->setText("mian menu");
    ui->pushButton_4->setVisible(false);
    ui->textEdit->setVisible(false);
    this->sub = new SubWindow(this);
    this->sub2 = new sub2Window(this);
    QPixmap pixmap  = QPixmap(":/new/prefix1/1.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    op = new sqlOperator();
}
void MainWindow::onNewconnect()
{

    socket = server->nextPendingConnection();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot1(){

    this->sub2->show();
    this->hide();


}

void MainWindow::slot2(){
    this->sub->show();
    this->hide();
}


void MainWindow::slot3(){
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(true);
    ui->textEdit->setVisible(true);
    ui->label->setText(tr("统计"));
    QString doc = op->getNumOfDoc();

    QString  pat =  op->getNumOfPat();
    string str = doc.toStdString()+pat.toStdString();
    ui->textEdit->setText(tr(str.c_str()));
   // qDebug()<<doc;
   // qDebug()<<pat;
    std::cout<<doc.toStdString()<<endl;
    std::cout<<pat.toStdString()<<endl;
}

void MainWindow::slot4(){
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->label->setText(tr("医院门诊系统"));
}
