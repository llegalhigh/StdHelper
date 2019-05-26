#ifndef TABLEITEM_H
#define TABLEITEM_H

#include "qgraphicstableitem.h"

#include <QDateTime>
#include <QGraphicsItem>
#include <QList>


class ClassTable;
class TableColumn;

class TableItem {
public:
    //构造函数
    TableItem( const QString, const QDateTime, const QDateTime, ClassTable * );
    //析构函数
    virtual ~TableItem();

    //绘制
    void drawOnTable( QGraphicsScene * ) const;

    void    setText( const QString );
    QString getText() const;

    template< typename T >
    static bool haveIntersection( T &start1, T &end1, T &start2, T &end2 );

protected:
    void findParentColumns();

    ClassTable *parentTablePtr;

    //显示的文字
    QString text;
    //边框粗细
    qreal borderWidth = 4;

    QDateTime start;
    QDateTime end;

    QList< TableColumn * >        parentColumnPtrList;
    QList< QGraphicsTableItem * > childQGraphicsItemPtrList;
};

#endif   // TABLEITEM_H
