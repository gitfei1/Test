#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log.h"
#include "roll.h"
#include<QtCore/QTextCodec>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<linux/rtc.h>
#include<sys/ioctl.h>
#include<linux/ioctl.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::CustomizeWindowHint);
    win=new log(this);
    ro = new roll(this);
    connect(ui->pushButton,SIGNAL(clicked())
            ,this,SLOT(on_loginBt_clicked()));
    //connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_buttun()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_roll_clicked()));

        QPixmap pixmap=QPixmap(":/new/prefix1/9.jpg").scaled(this->size());
        QPalette palette (this->palette());
        palette.setBrush(QPalette::Background,QBrush(pixmap));
        this->setPalette(palette);



        printf("mainwindow!\n");
        device = new SoundDevice("", this);

		/*建立连接并开始接收数据*/
        socket = new QTcpSocket(this);
        socket->connectToHost(QString("192.168.46.65"), 1100);
        connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

        connect(ro,SIGNAL(sendsignal()),this,SLOT(reshow()));
        connect(win,SIGNAL(sendsignal()),this,SLOT(reshow()));
       // ui->lineEdit->setText((QString::fromLocal8Bit("Please  Keep  quiet")));
        //cout << "connect server ok" << endl;
        start();
        printf("already!\n");
       // QString str ="第1号诊室就诊";
       // ui->lineEdit_2->setText(tr("第1号诊室就诊"));
       // ui->lineEdit_3->setText(str);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBt_clicked()
{
    //检查用户和密码

    //如果正确就进入到主界面(不需要返回到登录界面)
    win->show();
    this->hide();
   //这里不能用delete，因为this是main函数中创建的栈空间系统自动释放
}

void MainWindow::on_buttun(){
    this->parentWidget()->show();
    this->close();

}

void MainWindow::reshow(){
    this->show();
}

void MainWindow::on_roll_clicked()
{
    //检查用户和密码

    //如果正确就进入到主界面(不需要返回到登录界面)
    ro->show();
    this->hide();
   //这里不能用delete，因为this是main函数中创建的栈空间系统自动释放
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::quit() {
    close();
}

void MainWindow::start(QByteArray byteArray) {
    QTextCodec *pTextCodeUTF = QTextCodec::codecForName("UTF-8");
    QString byteStr = pTextCodeUTF->toUnicode(byteArray);
    wchar_t ss[byteStr.length()];
    int j=0;
    for(int i=0; i<byteStr.length(); i++) {
        printf("%0x\t", byteStr.at(i).unicode());
        if(byteStr.at(i).unicode()) {
            ss[j++] = byteStr.at(i).unicode();
        }
    }

    device->soudText(ss);
}
void MainWindow::stop() {
    device->stop();
}
void MainWindow::pause() {
    device->pause();
}
void MainWindow::start() {
    device->start();
}
//读取数据并且显示到lcd屏，调用led闪烁
void MainWindow::readData() {
	printf("receive data now!\n");
    char buffer[1024];
    memset(buffer, 0x00, sizeof(buffer));
    int rs = socket->read(buffer, sizeof(buffer));
	if(rs == -1) 
		printf("read data error!\n");
	else
	{
        //socket->flush();
        ui->label->setText(buffer);
        printf("%s\n",buffer);
        buzz();
        led();
		QByteArray byteArray(buffer, rs);
		start(byteArray);
	}
}
//led闪烁
void MainWindow::led()
{
	int leds_fd,ret;
   leds_fd=::open("/dev/leds",O_RDWR);
   if(leds_fd==-1)
    {
         printf("open /dev/leds failed!\n");
    }
   else
    {
        printf("open /dev/leds successfully!");
        ret=::ioctl(leds_fd,1,1);
        ret=::ioctl(leds_fd,1,0);
        sleep(1);
        ret=::ioctl(leds_fd,0,1);
        ret=::ioctl(leds_fd,0,0);
    }
   ::close(leds_fd);
}

void MainWindow::buzz()
{
	int fd;
	char *buzzer = "/dev/buzzer_ctl";
	//BuzzerOnOffTimes = 3;
	
	printf("buzzer light on and off 5 times \r\n");
	
    if((fd = ::open(buzzer, O_RDWR|O_NOCTTY|O_NDELAY))<0)
	printf("open %s failed\n",buzzer);   
	else
	{	
    	printf("open %s success\r\n",buzzer);
            ::ioctl(fd,1);	//parameter 2 is cmd ,cmd = 1 buzzer on
            ::ioctl(fd,0);
    }
    ::close(fd);
}
