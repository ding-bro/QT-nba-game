#include "mainwindow.h"
#include <QApplication>
#include"setdata.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    // 测试关卡数据
//    setdata data;

//    for(int i=0;i<4;i++)
//    {
//        for(int j=0;j<4;j++)
//        {
//            qDebug()<<data.mdata[1][i][j];  // 关卡数，i行j列
//        }
//     qDebug()<<" ";
//    }


    return a.exec();
}
