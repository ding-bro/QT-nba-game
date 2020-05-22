#include "select_level.h"
#include<QPainter>
#include<QMenuBar>
#include"mypushbutton.h"
#include<QDebug>
#include"mainwindow.h"
#include<QTimer>
#include<QLabel>
#include<QSound>


select_level::select_level(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(405,715);

    this->setWindowIcon(QPixmap(":/QT_photo/篮球火.png"));

    this->setWindowTitle("选择关卡");

    // 创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    // 创建开始菜单
    QMenu *menu= bar->addMenu("开始");
    //bar->addMenu("退出");

    // 添加子选项
    QAction*quit=menu->addAction("退出");

    // 退出功能
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });



    // 返回按钮
    mypushbutton *back=new mypushbutton(":/QT_photo/返回2.png",":/QT_photo/返回22.png");
    back->setParent(this);

    back->move(this->width()-back->width(),this->height()-back->height());

    connect(back,&mypushbutton::clicked,[=](){
            QSound *sound=new QSound(":/QT_photo/开始音效.wav");
            sound->play();

            qDebug()<<"点击";
     });

    // 返回功能
    connect(back,&mypushbutton::clicked,[=](){
              QTimer::singleShot(300,this,[=](){   // 延时返回
              emit this->choeseback();  // 自定义返回信号
              this->hide();  // 隐藏本窗口
              MainWindow *main=new MainWindow;  // 显示上一级窗口
              main->show();

          });

      });




    // 篮球
    for(int i=0;i<20;i++)  // 一个for写出二维矩阵  行数：每4个一组数，取模结果为为0,1,2,3。    列数，每4个为一组，结果一次为1，2，3...循环
    {   // 在乘以一个数作为间隔
         mypushbutton *ball=new mypushbutton(":/QT_photo/篮球11.png");
         ball->setParent(this);
         ball->move(25+i%4*90,130+i/4*90);

         connect(ball,&mypushbutton::clicked,[=](){
             QSound *sound=new QSound(":/QT_photo/篮球音效.wav");
             sound->play();

             QString str=QString("您选择的是第%1关").arg(i+1);
             qDebug()<<str;

             // 进入游戏场景
             this->hide(); // 隐藏窗口
             play = new play_level(i+1); // new出对象
             play->show();  // 显示窗口

         });



         // 添加文本序号
         // ball->setText(QString::number(i+1));
         QLabel *text=new QLabel;
         text->setParent(this);
         text->setFixedSize(ball->width(),ball->height()); // 设置文本框的大小跟label的大小一样
         text->setText(QString::number(i+1));
         text->move(25+i%4*90,130+i/4*90);  // 设置文字位置

         text->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         text->setAttribute(Qt::WA_TransparentForMouseEvents); // 穿透

    }



}


void select_level::paintEvent(QPaintEvent *event)
{
    // 背景
    QPainter paint(this);
    QPixmap pix;

    pix.load(":/QT_photo/背景4.jpeg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);

}















