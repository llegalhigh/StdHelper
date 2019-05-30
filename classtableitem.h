#ifndef CLASSTABLEITEM_H
#define CLASSTABLEITEM_H

#include "tableitem.h"

#include <QString>


class ClassTableItem : public TableItem {
public:
    ClassTableItem();

protected:
    QString       className;
    QString       classPlace;
    QString       teacherName;
    QList< bool > isInWeek;
    QTime         startTime;
    QTime         endTime;
};

#endif   // CLASSTABLEITEM_H
