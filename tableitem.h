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
    //构造函数
    TableItem( const QString   itemText  = "",
               const QDateTime st        = QDateTime::currentDateTime(),
               const QDateTime ed        = QDateTime::currentDateTime(),
               ClassTable *    parentPtr = nullptr );
    //析构函数
    virtual ~TableItem();

    void show();
    void hide();

    //绘制
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

    //辅助函数
    template< typename T >
    static bool haveIntersection( T &start1, T &end1, T &start2, T &end2 );

protected:
    void findParentColumns();
    //上级ClassTable
    ClassTable *parentTablePtr;

    //显示的文字
    QString text;
    //边框
    qreal borderWidth = 4;                                              //粗细
    QPen  borderPen = QPen( QBrush( Qt::white ), this->borderWidth );   //颜色
    //底色
    QBrush fillBrush = QBrush( QColor( 0, 0, 255, 50 ) );

    //开始结束事件
    QDateTime start;
    QDateTime end;

    //上级TableColumn
    QList< TableColumn * > parentColumnPtrList;
    //下级QGraphicsTableItem
    QList< QGraphicsTableItem * > childQGraphicsItemPtrList;
};

#endif   // TABLEITEM_H
