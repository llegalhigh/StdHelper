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
    //���캯��
    TableItem( const QString, const QDateTime, const QDateTime, ClassTable * );
    //��������
    virtual ~TableItem();

    //����
    void drawOnTable( QGraphicsScene * ) const;

    void    setText( const QString );
    QString getText() const;

    template< typename T >
    static bool haveIntersection( T &start1, T &end1, T &start2, T &end2 );

protected:
    void findParentColumns();

    ClassTable *parentTablePtr;

    //��ʾ������
    QString text;
    //�߿��ϸ
    qreal borderWidth = 4;

    QDateTime start;
    QDateTime end;

    QList< TableColumn * >        parentColumnPtrList;
    QList< QGraphicsTableItem * > childQGraphicsItemPtrList;
};

#endif   // TABLEITEM_H
