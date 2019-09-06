#include "subwindow.h"
#include "ui_subwindow.h"
#include <QDesktopWidget>
#include"mainwindow.h"
#include<iostream>
using namespace std;

SubWindow::SubWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubWindow)
{
    //((MainWindow*)parent)-
    this->parent=parent;
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    QPixmap pixmap  = QPixmap(":/new/prefix1/2.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->lineEdit_6->setVisible(false);
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    login = 0;
    reg = 0;
    ser = 0;

}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::slot1(){
    if(ser ==0){

        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(false);
        ui->lineEdit_6->setVisible(false);

    ui->pushButton->setVisible(false);
   // ui->pushButton_2->setVisible(false);
    ui->pushButton_1->setText(tr("登陆"));
    ui->pushButton_2->setText(tr("退出"));
    ui->lineEdit_3->setPlaceholderText(tr("登陆账号"));
    ui->lineEdit_4->setPlaceholderText(tr("密码"));
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    login = 1;
    }
    else {
        qDebug ()<<tr(patInf.toStdString().c_str());//网络发包
        qDebug()<<patInf.toUtf8();
        //cout<<patInf.toUtf8()<<endl;
        ((MainWindow*)parent)->socket->write(patInf.toStdString().c_str());
    }
}

void SubWindow::slot2(){
    if(reg ==0 && login ==0 &&ser==0){
    ui->lineEdit->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_1->setText(tr("确认"));
    reg  = 1;
    }
    else if(reg ==1) {
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
        ui->lineEdit_6->setVisible(false);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
        QString str1 =ui->lineEdit->text();
        QString str2 =ui->lineEdit_2->text();
        QString str3 =ui->lineEdit_3->text();
        QString str4 =ui->lineEdit_4->text();
        QString str5 =ui->lineEdit_5->text();
        QString str6 =ui->lineEdit_6->text();
       bool flag = ((MainWindow*)parent)->op->signUpDocInfo(str1.toUtf8(),str2,str3,str4,str5,str6);
       if(flag) ui->label_2->setText(tr("注册成功"));
       else ui->label_2->setText(tr("注册失败"));
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->pushButton_1->setText(tr("注册"));
        reg = 0 ;

    }
    else if(login ==1){
        QString account = ui->lineEdit_3->text();
        QString pwd = ui->lineEdit_4->text();
        bool flag =((MainWindow*)parent)->op->signInDocInfo(account.toUtf8(),pwd);
        if(flag) {
        ui->label_2->setText(tr("登录成功，点击开始叫号"));
        RoomNum = ((MainWindow*)parent)->op->getDocRoomNum(account.toUtf8());
       ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
        ui->lineEdit_6->setVisible(false);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->pushButton->setText(tr("呼叫病人"));
        ui->pushButton_1->setText(tr("下一个"));
        ui->pushButton_2->setText(tr("离开"));
       // ui->label_2->clear();
        login =0;
        ser = 1;
    }
        else ui->label_2->setText(tr("登录失败"));
    }
    else if(ser ==1){
        patInf = ((MainWindow*)parent)->op->getPatInfo(RoomNum);

        //QString str ="123";
        if(patInf==NULL)  ui->label_2->setText(tr("目前无新病人登记"));
        else ui->label_2->setText(tr(patInf.toStdString().c_str()));
    }
}

void SubWindow::slot3(){
    if(ser ==1||login ==1){
        ui->pushButton->setText(tr("登陆"));
        ui->pushButton_1->setText(tr("注册"));
        ui->pushButton_2->setText(tr("退出"));

        ui->lineEdit_3->setPlaceholderText(tr("门诊号"));
        ui->lineEdit_4->setPlaceholderText(tr("部门号"));
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->label_2->clear();
        if(login ==1){
            ui->pushButton->setVisible(true);
            ui->lineEdit_3->setVisible(false);
            ui->lineEdit_4->setVisible(false);
            ui->lineEdit_4->setEchoMode(QLineEdit::Normal);
        }
        ser = 0;
        login = 0;

    }
    else{
    this->parentWidget()->show();
    this->close();
}
}
