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
    findParentColumns();   //寻找上级TableColumn
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
 * @brief   在上级ClassTable中寻找归属的TableColumn
 * @warning
 * @todo
 */
void TableItem::findParentColumns() {
    parentColumnPtrList.clear();
    childQGraphicsItemPtrList.clear();   //之前因为没加这个导致显示重叠
    for ( TableColumn *colPtr : parentTablePtr->columnList ) {
        QDateTime colStartTime = colPtr->start;
        QDateTime colEndTime   = colPtr->end;
        if ( haveIntersection( start, end, colStartTime, colEndTime ) ) {
            this->parentColumnPtrList.append( colPtr );
            colPtr->childrenItemPtrList.append( this );

            QDateTime startTime = qMax( colStartTime, this->start );
            QDateTime endTime   = qMin( colEndTime, this->end );

            // 设置边框
            QPen borderPen = QPen( QBrush( Qt::white ), this->borderWidth );
            borderPen.setJoinStyle(
                Qt::RoundJoin );   //提示old-style cast不用管
            int xPos = colPtr->getXPos()
                       + (int)( borderWidth / 2 );   //边框左上顶点X,Y坐标
            int yPos =
                colPtr->getYPos() + colPtr->itemYPosShouldBe( startTime );
            int rectWidth = colPtr->visibleWidth - (int)borderWidth;
            int rectHeight =
                colPtr->itemYPosShouldBe( endTime ) - yPos - (int)borderWidth;
            // 设置底色
            QBrush fillBrush = QBrush( QColor( 0, 0, 255, 50 ) );

            // 设置文字字体
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
 * @brief   判断两个区间[start1,end1]和[start2,end2]是否有交集
 * @warning 前提：1.类型T必须支持==,<,<=,>=等operator
 *               2.区间合法，start1<end1，start2<end2
 * @note    static
 */
template< typename T >
bool TableItem::haveIntersection( T &start1, T &end1, T &start2, T &end2 ) {
    return start1 == start2 || end1 == start2 || end1 == end2
           || ( start1 >= start2 && start1 < end2 )
           || ( start1 <= start2 && ( end1 >= start2 || end1 >= end2 ) );
}
