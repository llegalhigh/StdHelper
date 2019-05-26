#include "qgraphicstableitem.h"


QGraphicsTableItem::QGraphicsTableItem( TableColumn *parentCol, int xPos,
                                        int yPos, int width, int height,
                                        QPen borderPen, QBrush fillBrush,
                                        QString text, QColor textColor,
                                        QFont textFont )
    : parentColumnPtr( parentCol ), backgroundItemPtr( new QGraphicsRectItem(
                                        xPos, yPos, width, height, this ) ),
      textItemPtr( new QGraphicsTextItem( text, this ) ) {
    //利用父类的构造函数
    QGraphicsRectItem( xPos, yPos, width, height );

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
