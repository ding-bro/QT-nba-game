#ifndef SETDATA_H
#define SETDATA_H

#include <QObject>
#include<QMap>
#include<QVector>

class setdata : public QObject
{
    Q_OBJECT
public:
    explicit setdata(QObject *parent = 0);


public:
    QMap<int,QVector<QVector<int>>> mdata;  // QMap<关卡数，二维数组>


public slots:
};

#endif // SETDATA_H
