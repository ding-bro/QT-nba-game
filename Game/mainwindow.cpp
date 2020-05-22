#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mypushbutton.h"  // 自定义按钮
#include"select_level.h" // 下一个场景
#include<QTimer>
#include<QSound> // 添加声音头文件  在pro文件中添加 QT += multimedia



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口固定大小
    setFixedSize(405,715);
    // 设置标题按钮图片
    this->setWindowIcon(QPixmap(":/QT_photo/篮球火.png"));
    // 设置标题
    this->setWindowTitle("NBA_Kobe_Game");
    // 退出功能
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });


    // 开始按钮
    mypushbutton *btn=new mypushbutton(":/QT_photo/关闭.png");
    btn->setParent(this); // 设置当前父类窗口中

    // 设置位置
    btn->move(this->width()*0.5-btn->width()*0.5,this->height()*0.75); // 让开始按钮在下方的中间位置，  屏幕宽度/2-按钮宽度/2


    QSound * sound=new QSound(":/QT_photo/开始音效.wav");

    // 设置按钮动画弹起效果
    connect(btn,&mypushbutton::clicked,[=](){
        btn->up();
        btn->down();   // 弹起效果
        sound->play();


// 延时示例
//int main(int argc, char *argv[])
//{
//   QApplication app(argc, argv);
//   QTimer::singleShot(600000, &app, SLOT(quit()));
//   return app.exec();
//}
        QTimer::singleShot(300,[=](){  // 延时200ms进行
            this->hide(); // 本窗口隐藏
            level->show();  // 场景出现
        });



    });

}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this); // 画家类
    QPixmap pix;  // 图片类

    pix.load(":/QT_photo/背景1.jpg");  // 加载图片
    paint.drawPixmap(0,0,this->width(),this->height(),pix); // 拉伸图片至窗口尺寸

    pix.load(":/QT_photo/文字.png"); // 加入图标
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5); // 自定义设置图标的尺寸大小
    // 返回的是一个新pix
    paint.drawPixmap(0,10,pix);

}





MainWindow::~MainWindow()
{
    delete ui;
}











