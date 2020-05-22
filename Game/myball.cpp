#include "myball.h"
#include<QDebug>

//myball::myball(QWidget *parent) : QPushButton(parent)
//{

//}


myball::myball(QString btnimg)
{
    QPixmap pix;
    bool ret=pix.load(btnimg);
    if(ret==false)
    {
        QString str=QString("图片%1加载失败!"); // 显示加载失败的图片路径
        qDebug()<<str.arg(btnimg);
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


    // 实例化定时器
    time1=new QTimer(this);
    time2=new QTimer(this);


    // 连接黑球翻篮球的信号
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/QT_photo/翻转%1").arg(this->min++); // 翻转1->翻转10
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        // 翻转完成之后将min重置为1,不能让min一直++
        if(this->min>this->max)
        {
            this->min=1;
            this->isaction=false; // 停止翻转
            time1->stop();
        }
    });


    // 连接篮球翻黑球的信号
    connect(time2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/QT_photo/翻转%1").arg(this->max--); // 翻转10->翻转1
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max<this->min)  // 不让max一直--
        {
            this->max=10;
            this->isaction=false;
            time2->stop();
        }
    });
}


// 重写鼠标按下事件
void myball::mousePressEvent(QMouseEvent *e)
{
   if(this->isaction || this->iswin)  // 当翻转效果完成之后return
   {
       return;                        // 当游戏胜利之后，重写按下事件，阻塞篮球按钮
   }
   else
   {
       QPushButton::mousePressEvent(e);
   }
}



void myball::changeflag()  // 实现翻转
{
    // 黑球->篮球
    if(this->flag)
    {
        time1->start(40); // 40ms执行
        this->isaction=true; // 开始翻转
        this->flag=false; // 置为篮球(0)
    }
    else // 篮球->黑球
    {
        time2->start(40);
        this->isaction=true;  // 开始翻转
        this->flag=true; // 置为黑球(1)
    }
}















