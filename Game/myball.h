#ifndef MYBALL_H
#define MYBALL_H

#include <QPushButton>
#include<QTimer>

class myball : public QPushButton
{
    Q_OBJECT
public:
    //explicit myball(QWidget *parent = nullptr);

    // 传入图片的路径
    myball(QString btnimg);

    int posx;  // x坐标
    int posy;  // y坐标
    bool flag; // 标志黑球或篮球

    void changeflag();  // 改变黑球和篮球，实现翻转功能
    QTimer *time1;  // 黑球翻篮球定时器
    QTimer *time2;  // 篮球翻黑球定时器
    int min=1;  // 翻转图片最小值
    int max=10;  // 翻转图片最大值


    // 是否执行翻转效果
    bool isaction=false;


    // 重写按下事件状态
    // 为了防止用户快速点击造成的bug，让点击按钮之后，执行完翻转效果后，才能再次点击按钮执行翻转
    void mousePressEvent(QMouseEvent *e);


    // 判断是否胜利
    bool iswin=false;


signals:

public slots:
};















#endif // MYBALL_H
