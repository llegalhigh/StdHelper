#include "qgraphicstableitem.h"
#include "tablecolumn.h"

QGraphicsTableItem::QGraphicsTableItem( TableColumn *parentCol,
                                        TableItem *parentItem, int xPos,
                                        int yPos, int width, int height,
                                        QPen borderPen, QBrush fillBrush,
                                        QString text, QColor textColor,
                                        QFont textFont )
    :   //初始化自己，并指定自己的parent TableColumn
      QGraphicsRectItem( xPos, yPos, width, height, parentCol ),
      parentColumnPtr( parentCol ), parentItemPtr( parentItem ),
      //初始化child，指定自己为他们的parent
      backgroundItemPtr(
          new QGraphicsRectItem( xPos, yPos, width, height, this ) ),
      textItemPtr( new QGraphicsTextItem( text, this ) ) {
    backgroundItemPtr->setPen( borderPen );
    backgroundItemPtr->setBrush( fillBrush );

    textItemPtr->setDefaultTextColor( textColor );
    textItemPtr->setPos( xPos, yPos );
    textItemPtr->setTextWidth( width );
    textItemPtr->setFont( textFont );
}

void QGraphicsTableItem::paint( QPainter *                      painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *                       widget ) {
    backgroundItemPtr->paint( painter, option, widget );
    textItemPtr->paint( painter, option, widget );
}

void QGraphicsTableItem::resize( QResizeEvent *tableEvent ) {
    //设置自己
    QGraphicsRectItem( ClassTable::scaleSize( this->rect(), tableEvent ) );
    //设置背景
    backgroundItemPtr->setRect(
        ClassTable::scaleSize( backgroundItemPtr->rect(), tableEvent ) );
    //设置文字
    textItemPtr->setPos(
        ClassTable::scaleSize( textItemPtr->pos(), tableEvent ) );
    textItemPtr->setTextWidth( textItemPtr->textWidth()
                               * tableEvent->size().width()
                               / tableEvent->oldSize().width() );
}

void QGraphicsTableItem::resize( int xPos, int yPos, int width, int height ) {
    //设置自己
    QGraphicsRectItem( xPos, yPos, width, height );
    //设置背景
    backgroundItemPtr->setRect( xPos, yPos, width, height );
    //设置文字
    textItemPtr->setPos( xPos, yPos );
    textItemPtr->setTextWidth( width );
}
