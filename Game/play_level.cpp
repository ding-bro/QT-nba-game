#include "play_level.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include"select_level.h"
#include<QLabel>
#include"myball.h"
#include"setdata.h"
#include<QPropertyAnimation>
#include<QSound>


play_level::play_level(int levelnum)
{
    QString str=QString("进入第%1关").arg(levelnum);
    qDebug()<<str;
    this->levelindex=levelnum;


    this->setFixedSize(405,715);

    this->setWindowIcon(QPixmap(":/QT_photo/篮球火.png"));

    this->setWindowTitle("游戏场景");

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

        QTimer::singleShot(300,this,[=](){
            emit this->chooseback();
            this->hide();
            select_level *select=new select_level;
            select->show();
        });       
    });


    // 关卡标识
    QLabel *label=new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("微软雅黑"); // 设置字体
    font.setPointSize(20); // 字体大小

    // 字体与QLabel关联
    label->setFont(font);
    QString str1=QString("LEVEL:%1").arg(this->levelindex);
    label->setText(str1);
    label->setGeometry(5,this->height()-50,120,50);  // 设置文本框大小


    // 初始化每个关卡的二维数组
    setdata data;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gamearray[i][j]=data.mdata[this->levelindex][i][j];
            // 把QMap的int类型去除,留下二维数组
        }
    }



    // 提前设置胜利图片在屏幕之外
    QLabel *winlabel=new QLabel;
    QPixmap pix;
    pix.load(":/QT_photo/成功.png");
    winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->setPixmap(pix);
    winlabel->setParent(this);
    winlabel->move(this->width()-pix.width()-65,-pix.height());  // 胜利在屏幕之外防止，方便后来的动画砸下效果









    // 添加按钮背景
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            // 绘制按钮背景图片
            QLabel *label=new QLabel;
            label->setGeometry(0,0,80,80); // 文本框大小
            label->setPixmap(QPixmap(":/QT_photo/按钮背景.png"));  // pix.width()/pix.height()
            label->setParent(this);
            label->move(5+i*100,165+j*100);
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);


            // 创建点击ball
            QString str;
            if(this->gamearray[i][j]==1) // 1=黑球
            {
               // 显示黑球
               str=":/QT_photo/黑球2.png";
            }
            else  // 0=篮球
            {
              // 显示篮球
               str=":/QT_photo/卡通篮球2.png";
            }



            myball*ball=new myball(str); // 将str放入，判断黑球和篮球的位置
            ball->setParent(this);
            ball->move(10+i*100,170+j*100);


            // 球赋值
            ball->posx=i;  // x=行
            ball->posy=j;  // y=列
            ball->flag=this->gamearray[i][j]; // flag本质是0和1   1是黑球  0是篮球


            // 将球放入二维数组中，以便后期的维护
            btnball[i][j]=ball;



            // 翻转信号
            connect(ball,&myball::clicked,[=](){
                QSound *sound=new QSound(":/QT_photo/篮球音效.wav");
                sound->play();

                ball->changeflag();
                this->gamearray[i][j]=this->gamearray[i][j]==0 ? 1 : 0; // 更新二维数组
                // 如果等于篮球置为黑球，等于黑球置为篮球

                QTimer::singleShot(300,[=](){  // 延时
                    // 翻转周围的球
                    if(ball->posx+1<=3)  // x坐标+1，向右侧翻转
                    {
                        btnball[ball->posx+1][ball->posy]->changeflag();
                        this->gamearray[ball->posx+1][ball->posy]=this->gamearray[ball->posx+1][ball->posy]==0 ? 1 : 0;
                    }
                    if(ball->posx-1>=0)  // x坐标-1，向左侧翻转
                    {
                        btnball[ball->posx-1][ball->posy]->changeflag();
                        this->gamearray[ball->posx-1][ball->posy]=this->gamearray[ball->posx-1][ball->posy]==0 ? 1 : 0;
                    }
                    if(ball->posy+1<=3)  // y坐标+1，向下侧翻转
                    {
                        btnball[ball->posx][ball->posy+1]->changeflag();
                        this->gamearray[ball->posx][ball->posy+1]=this->gamearray[ball->posx][ball->posy+1]==0 ? 1 : 0;
                    }
                    if(ball->posy-1>=0)  // y坐标-1，向上侧翻转
                    {
                        btnball[ball->posx][ball->posy-1]->changeflag();
                        this->gamearray[ball->posx][ball->posy-1]=this->gamearray[ball->posx][ball->posy-1]==0 ? 1 : 0;
                    }



                    // 显示胜利         所有篮球置为黑球便是胜利 0->1
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(btnball[i][j]->flag==false)  // 有一个是篮球，则为失败
                            {
                                this->iswin=false;
                            }
                        }
                    }
                    if(this->iswin==true)
                    {
                        qDebug()<<"游戏胜利";
                        // 胜利之后，禁用所有球的按钮
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                btnball[i][j]->iswin=true; // 胜利之后，将myball中的iswin置为true
                            }
                        }
                        // 将胜利图片做砸下效果
                        QSound *sound=new QSound(":/QT_photo/胜利音效.wav");
                        sound->play();

                        // 砸下效果
                        this->up(winlabel);
                    }



                });

            });


        }
    }










}




void play_level::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix;
    pix.load(":/QT_photo/背景2.jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
}


void play_level::up(QLabel *label)
{
    QPropertyAnimation * move=new QPropertyAnimation(label,"geometry");
    move->setDuration(1000);
    move->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
    move->setEndValue(QRect(label->x(),label->y()+150,label->width(),label->height()));
    move->setEasingCurve(QEasingCurve::OutBounce);
    move->start();
}













