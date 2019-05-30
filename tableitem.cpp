#include "classtable.h"
#include "tablecolumn.h"
#include "tableitem.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>


TableItem::TableItem( const QString itemText, const QDateTime st,
                      const QDateTime ed, ClassTable *parentPtr )
    : parentTablePtr( parentPtr ), start( st ), end( ed ) {
    setText( itemText );
    findParentColumns();   //Ѱ���ϼ�TableColumn
}

TableItem::~TableItem() {
    for ( QGraphicsItem *itemPtr : childQGraphicsItemPtrList ) {
        delete itemPtr;
    }
}

void TableItem::show() {
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->show();
    }
}

void TableItem::hide() {
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->hide();
    }
}

void TableItem::drawOnTable( QGraphicsScene *scene ) const {
    qDebug() << "\t\tStart TableItem {";
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        qDebug() << "\t\t\tStart QGraphicsTableItem "
                 << itemPtr->textItemPtr->toPlainText();
        parentTablePtr->scenePtr->addItem( itemPtr );
    }
    qDebug() << "\t\t} Finish TableItem";
}

void TableItem::resize( QResizeEvent *tableEvent ) {
    for ( QGraphicsTableItem *childItemPtr : childQGraphicsItemPtrList ) {
        childItemPtr->resize( tableEvent );
    }
}

void TableItem::setText( const QString text ) {
    this->text = text;
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->textItemPtr->setPlainText( text );
    }
}

/**
 * @brief   ���ϼ�ClassTable��Ѱ�ҹ�����TableColumn
 * @warning
 * @todo
 */
void TableItem::findParentColumns() {
    parentColumnPtrList.clear();
    childQGraphicsItemPtrList.clear();   //֮ǰ��Ϊû�����������ʾ�ص�
    for ( TableColumn *colPtr : parentTablePtr->columnList ) {
        QDateTime colStartTime = colPtr->start;
        QDateTime colEndTime   = colPtr->end;
        if ( haveIntersection( start, end, colStartTime, colEndTime ) ) {
            this->parentColumnPtrList.append( colPtr );
            colPtr->childrenItemPtrList.append( this );

            QDateTime startTime = qMax( colStartTime, this->start );
            QDateTime endTime   = qMin( colEndTime, this->end );

            // ���ñ߿�
            QPen borderPen = QPen( QBrush( Qt::white ), this->borderWidth );
            borderPen.setJoinStyle(
                Qt::RoundJoin );   //��ʾold-style cast���ù�
            int xPos = colPtr->getXPos()
                       + (int)( borderWidth / 2 );   //�߿����϶���X,Y����
            int yPos =
                colPtr->getYPos() + colPtr->itemYPosShouldBe( startTime );
            int rectWidth = colPtr->visibleWidth - (int)borderWidth;
            int rectHeight =
                colPtr->itemYPosShouldBe( endTime ) - yPos - (int)borderWidth;
            // ���õ�ɫ
            QBrush fillBrush = QBrush( QColor( 0, 0, 255, 50 ) );

            // ������������
            QFont textFont;
            textFont.setBold( true );
            textFont.setPointSize( 8 );

            QGraphicsTableItem *childItemPtr = new QGraphicsTableItem(
                colPtr, this, xPos, yPos, rectWidth, rectHeight, borderPen,
                fillBrush, text );
            childItemPtr->setFlags( QGraphicsItem::ItemIsSelectable );

            this->childQGraphicsItemPtrList.append( childItemPtr );
            colPtr->childQGraphicsItemPtrList.append( childItemPtr );
        }
    }
}

/**
 * @brief   �ж���������[start1,end1]��[start2,end2]�Ƿ��н���
 * @warning ǰ�᣺1.����T����֧��==,<,<=,>=��operator
 *               2.����Ϸ���start1<end1��start2<end2
 * @note    static
 */
template< typename T >
bool TableItem::haveIntersection( T &start1, T &end1, T &start2, T &end2 ) {
    return start1 == start2 || end1 == start2 || end1 == end2
           || ( start1 >= start2 && start1 < end2 )
           || ( start1 <= start2 && ( end1 >= start2 || end1 >= end2 ) );
}
