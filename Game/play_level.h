#ifndef PLAY_LEVEL_H
#define PLAY_LEVEL_H

#include <QMainWindow>
#include"myball.h"
#include<QLabel>

class play_level : public QMainWindow
{
    Q_OBJECT
public:
    //explicit play_level(QWidget *parent = nullptr);

    play_level(int levelnum); // 关卡数
    int levelindex;

    void paintEvent(QPaintEvent *event);

    int gamearray[4][4]; // 维护 map中的二维数组数据
    // map<int,vector<vector<int>>>  使用难度大
    // map中的int关卡数已经在levelnum传进过一次
    // 只留下map中的二维数组数据


    // 维护球的数据
    myball * btnball[4][4];


    // 是否胜利
    bool iswin=true;


    void up(QLabel *label);




signals:
    void chooseback();

public slots:
};

#endif // PLAY_LEVEL_H






