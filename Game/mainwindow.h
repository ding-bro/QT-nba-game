#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"select_level.h" // 下一个场景

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    // 绘图事件
    void paintEvent(QPaintEvent *event);

    // 创建场景对象
    select_level *level=new select_level;


    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
