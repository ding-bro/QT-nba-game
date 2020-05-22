#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>   // 控件最终继承的父类是QPushButton

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr); // explicit：防止隐式类型转换使用构造函数


    mypushbutton(QString usuallypath,QString presspath="");
    // ①默认显示图片的路径
    // ②按下按钮之后的图片路径
    // 用于封装按钮的动画效果

    QString usuallypath;  // 成员属性，用于保存显示图片的路径
    QString presspath;  // 保存按下按钮后的图片路径

    void up();  // 向上跳动效果
    void down(); // 向下跳动效果


    // 重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);


signals:

public slots:
};

#endif // MYPUSHBUTTON_H






