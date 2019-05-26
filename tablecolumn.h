#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include "classtable.h"
#include "tableitem.h"

#include <QDateTime>
#include <QGraphicsRectItem>
#include <QList>


class TableColumn : public QGraphicsRectItem {
    friend class ClassTable;
    friend class TableItem;

public:
    //构造函数，指定所属的ClassTable
    TableColumn( int, QDateTime, QDateTime, ClassTable * = nullptr );
    //析构函数
    ~TableColumn();

    void setStart( QDateTime );
    void setEnd( QDateTime );

    int    getXPos() const;
    int    getYPos() const;
    qint64 getTimeLen() const;

    static int itemYPosShouldBe( QDateTime itemStart, QDateTime colStart,
                                 QDateTime colEnd, int colHeight );
    int        itemYPosShouldBe( QDateTime itemStart ) const;

    //绘制
    void drawOnTable() const;

protected:
    //上级ClassTable的指针
    ClassTable *parentTablePtr;
    //下级TableItem的指针们
    QList< TableItem * > childrenItemPtrList;

    //列的名称，比如“星期二”
    QString name;
    //列的编号，比如2
    int index;
    //列的宽度、高度，基于ClassTable的计算
    int width, height;
    int visibleWidth;

    //这一列上边缘代表的时间，比如5月25日00:00:00
    QDateTime start;
    //下边缘代表的时间，比如5月25日23:59:59
    QDateTime end;
};

#endif   // TABLECOLUMN_H
