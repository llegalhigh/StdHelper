#ifndef SUBCLASS_H
#define SUBCLASS_H

#include "classtable.h"
#include "qgraphicstableitem.h"

#include <QList>
#include <QTime>

/**
 * @brief (概念，课表上同一个格子就算做同一个Subclass)
 */
class Subclass {
    friend class ClassTableItem;

public:
    explicit Subclass( ClassTable::dayOfWeek whichDay, QTime start, QTime end,
                       QString place = "" );

protected:
    ClassTable::dayOfWeek whichDayOfWeek;   //这节课星期几上
    QList< bool >         isInWeek;     //第x个bool=这节课第x周上不上
    QString               place = "";   //上课地点
    QTime                 startTime;    //开始时间
    QTime                 endTime;      //结束时间

    ClassTableItem *    parentClassItem;
    QGraphicsTableItem *qItem;
};

#endif   // SUBCLASS_H
