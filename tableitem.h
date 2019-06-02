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
    friend class Subclass;

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
    void setBorderPen( const QPen &pen );
    void setFillBrush( const QBrush &brush );
    // getter
    QString getText() const;
    QPen    getBorderPen() const;
    QBrush  getFillBrush() const;

    //��������
    template< typename T >
    static bool haveIntersection( T &start1, T &end1, T &start2, T &end2 );

protected:
    void findParentColumns();
    //�ϼ�ClassTable
    ClassTable *parentTablePtr;

    //��ʾ������
    QString text;
    //�߿�
    qreal borderWidth = 4;                                              //��ϸ
    QPen  borderPen = QPen( QBrush( Qt::white ), this->borderWidth );   //��ɫ
    //��ɫ
    QBrush fillBrush = QBrush( QColor( 0, 0, 255, 50 ) );

    //��ʼ�����¼�
    QDateTime start;
    QDateTime end;

    //�ϼ�TableColumn
    QList< TableColumn * > parentColumnPtrList;
    //�¼�QGraphicsTableItem
    QList< QGraphicsTableItem * > childQGraphicsItemPtrList;
};

#endif   // TABLEITEM_H
