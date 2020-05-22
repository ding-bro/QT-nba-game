#ifndef SELECT_LEVEL_H
#define SELECT_LEVEL_H

#include <QMainWindow>
#include"play_level.h"

class select_level : public QMainWindow
{
    Q_OBJECT
public:
    explicit select_level(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*event);

    // 游戏场景对象指针
    play_level *play=NULL;

signals:
    // 自定义返回信号
    void choeseback();

public slots:
};

#endif // SELECT_LEVEL_H
