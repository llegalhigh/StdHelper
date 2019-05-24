#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include "classtable.h"
#include "tableitem.h"
#include <QDateTime>
#include <QList>

class TableColumn {
public:
    //构造函数，指定所属的ClassTable
    explicit TableColumn(ClassTable * = nullptr);
    //析构函数
    ~TableColumn();

    void setStart(QDateTime);
    void setEnd(QDateTime);

    //绘制
    void drawOnTable() const;

private:
    //上级ClassTable的指针
    ClassTable *parentTablePtr;
    //下级TableItem的指针们
    QList<TableItem *> childrenItemPtrList;

    //列的名称，比如“星期二”
    QString name;
    //列的编号，比如2
    int index;
    //列的宽度、高度，由ClassTable的计算
    int width, height;

    //这一列上边缘代表的时间
    QDateTime start;
    //下边缘代表的时间
    QDateTime end;
};

#endif // TABLECOLUMN_H
