#include "qgraphicstableitem.h"
#include "tablecolumn.h"

QGraphicsTableItem::QGraphicsTableItem( TableColumn *parentCol,
                                        TableItem *parentItem, int xPos,
                                        int yPos, int width, int height,
                                        QPen borderPen, QBrush fillBrush,
                                        QString text, QColor textColor,
                                        QFont textFont )
    :   //��ʼ���Լ�����ָ���Լ���parent TableColumn
      QGraphicsRectItem( xPos, yPos, width, height, parentCol ),
      parentColumnPtr( parentCol ), parentItemPtr( parentItem ),
      //��ʼ��child��ָ���Լ�Ϊ���ǵ�parent
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
    //�����Լ�
    QGraphicsRectItem( ClassTable::scaleSize( this->rect(), tableEvent ) );
    //���ñ���
    backgroundItemPtr->setRect(
        ClassTable::scaleSize( backgroundItemPtr->rect(), tableEvent ) );
    //��������
    textItemPtr->setPos(
        ClassTable::scaleSize( textItemPtr->pos(), tableEvent ) );
    textItemPtr->setTextWidth( textItemPtr->textWidth()
                               * tableEvent->size().width()
                               / tableEvent->oldSize().width() );
}

void QGraphicsTableItem::resize( int xPos, int yPos, int width, int height ) {
    //�����Լ�
    QGraphicsRectItem( xPos, yPos, width, height );
    //���ñ���
    backgroundItemPtr->setRect( xPos, yPos, width, height );
    //��������
    textItemPtr->setPos( xPos, yPos );
    textItemPtr->setTextWidth( width );
}
