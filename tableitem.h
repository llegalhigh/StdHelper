#ifndef TABLEITEM_H
#define TABLEITEM_H

#include "qgraphicstableitem.h"

#include <QDateTime>
#include <QGraphicsItem>
#include <QList>


class ClassTable;
class TableColumn;

class TableItem {
    friend class ClassTable;

public:
    //���캯��
    TableItem( const QString   itemText  = "",
               const QDateTime st        = QDateTime::currentDateTime(),
               const QDateTime ed        = QDateTime::currentDateTime(),
               ClassTable *    parentPtr = nullptr );
    //��������
    virtual ~TableItem();

    void show();
    void hide();

    //����
    void drawOnTable( QGraphicsScene * ) const;
    void resize( QResizeEvent *tableEvent );

    // setter
    void setText( const QString );
    // getter
    QString getText() const;

    //��������
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
