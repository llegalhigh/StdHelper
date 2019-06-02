#ifndef SUBCLASS_H
#define SUBCLASS_H

#include "classtable.h"
#include "qgraphicstableitem.h"

#include <QList>
#include <QTime>

/**
 * @brief (����α���ͬһ�����Ӿ�����ͬһ��Subclass)
 */
class Subclass {
    friend class ClassTableItem;

public:
    explicit Subclass( ClassTable::dayOfWeek whichDay, QTime start, QTime end,
                       QString place = "" );

protected:
    ClassTable::dayOfWeek whichDayOfWeek;   //��ڿ����ڼ���
    QList< bool >         isInWeek;     //��x��bool=��ڿε�x���ϲ���
    QString               place = "";   //�Ͽεص�
    QTime                 startTime;    //��ʼʱ��
    QTime                 endTime;      //����ʱ��

    ClassTableItem *    parentClassItem;
    QGraphicsTableItem *qItem;
};

#endif   // SUBCLASS_H
