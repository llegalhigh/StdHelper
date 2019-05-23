#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QDateTime>
#include "classtable.h"
#include "tableitem.h"
#include <QList>

class TableColumn
{
public:
    explicit TableColumn(QDateTime, QDateTime, ClassTable* = nullptr);
    ~TableColumn();
    void setStart(QDateTime);
    void setEnd(QDateTime);

private:
    ClassTable *parentTablePtr;

    QDateTime start;
    QDateTime end;

    QList<TableItem *> childrenItemPtrList;
};

#endif // TABLECOLUMN_H
