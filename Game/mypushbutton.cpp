#include "mypushbutton.h"
#include<QDebug>
#include<QPixmap>
#include<QPushButton>
#include<QPropertyAnimation> // 动画效果头文件


//mypushbutton::mypushbutton(QWidget *parent) : QPushButton(parent)
//{

//}


mypushbutton::mypushbutton(QString usuallypath, QString presspath)
{
    this->usuallypath=usuallypath;  // 初始化成员属性
    this->presspath=presspath;

    QPixmap pix;  // 创建图片
    bool ret=pix.load(usuallypath);  // 加载图片路径   load返回值为bool
    // 判断是否加载成功
    if(ret==false)
    {
        qDebug()<<"图片加载失败！！！";
        return;
    }

    // 设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());  // 自动拉伸为合适大小

    // 设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");  // 使用的是CSS网页样式

    // 设置图标
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}

// QPropertyAnimation示例
//QPropertyAnimation *animation = new QPropertyAnimation(myWidget, "geometry");
//animation->setDuration(10000);
//animation->setStartValue(QRect(0, 0, 100, 30));
//animation->setEndValue(QRect(250, 250, 100, 30));
//animation->start()

void mypushbutton::up()
{
   QPropertyAnimation *move=new QPropertyAnimation(this,"geometry"); // "geometry" 矩形方框限制动画范围
   move->setDuration(200); // 动画间隔时间
   move->setStartValue(QRect(this->x(),this->y(),this->width(),this->height())); // 动画开始位置
   move->setEndValue(QRect(this->x(),this->y()-20,this->width(),this->height())); // 动画结束位置
   move->setEasingCurve(QEasingCurve::InOutQuad); // setEasingCurve 动作曲线QEasingCurve::OutInQuad,QEasingCurve::InCubic
   move->start();
}


void mypushbutton::down()
{
    QPropertyAnimation *btn1=new QPropertyAnimation(this,"geometry");
    btn1->setDuration(200);
    btn1->setStartValue(QRect(this->x(),this->y()-20,this->width(),this->height())); // 结束-开始，循环执行，达到跳动效果
    btn1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    btn1->setEasingCurve(QEasingCurve::InOutQuad);
    btn1->start();
}



void mypushbutton::mousePressEvent(QMouseEvent *e)
{
    if(this->presspath!="") // 传入的按下图片不为空
    {
        QPixmap pix;  // 创建图片
        bool ret=pix.load(this->presspath);  // 加载图片路径   load返回值为bool
        // 判断是否加载成功
        if(ret==false)
        {
            qDebug()<<"图片加载失败！！！";
            return;
        }

        // 设置图片固定大小
        this->setFixedSize(this->width(),this->height());  // 自动拉伸为合适大小

        // 设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");  // 使用的是CSS网页样式

        // 设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(this->width(),this->height()));

    }

    // 父类处理其他内容
    return QPushButton::mousePressEvent(e);

}

void mypushbutton::mouseReleaseEvent(QMouseEvent *e)
{

    if(this->presspath!="") // 传入的按下图片不为空
    {
        QPixmap pix;  // 创建图片
        bool ret=pix.load(this->usuallypath);  // 加载图片路径   load返回值为bool
        // 判断是否加载成功
        if(ret==false)
        {
            qDebug()<<"图片加载失败！！！";
            return;
        }

        // 设置图片固定大小
        this->setFixedSize(this->width(),this->height());  // 自动拉伸为合适大小

        // 设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");  // 使用的是CSS网页样式

        // 设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(this->width(),this->height()));

    }

     // 父类处理其他内容
    return QPushButton::mouseReleaseEvent(e);


}






























