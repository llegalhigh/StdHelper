#include "tablecolumn.h"

#include <QDebug>


TableColumn::TableColumn( int index, QDateTime start, QDateTime end,
                          ClassTable *parent, int xPos )
    : parentTablePtr( parent ), index( index ),
      width( parentTablePtr->width / parentTablePtr->getColumnNo() ),
      height( parentTablePtr->height ), visibleWidth( width * 7 / 8 ),
      start( start ), end( start <= end ? end : start ) {
    //���ø��๹�캯��
    QGraphicsRectItem( xPos, getYPos(), width, height );
    //���ñ�������
    bool includeNow = this->includeNow();
    backgroundItemPtr =
        new QGraphicsRectItem( xPos, 0, visibleWidth, height, this );
    backgroundItemPtr->setPen( QPen( QColor( 0, 0, 0, 0 ) ) );
    backgroundItemPtr->setBrush(
        QBrush( QColor( 0, 0, 0, includeNow ? 100 : 50 ) ) );
    backgroundItemPtr->setZValue( 1 );
    //����ʱ���ߣ�����еĻ���
    QDateTime curDT = QDateTime::currentDateTime();
    if ( includeNow ) {
        timeLineItemPtr =
            new QGraphicsLineItem( xPos, itemYPosShouldBe( curDT ),
                                   xPos + visibleWidth - timeLineWidth / 2,
                                   itemYPosShouldBe( curDT ), this );
        timeLineItemPtr->setPen(
            QPen( QBrush( timeLineColor ), timeLineWidth ) );
    } else {
        timeLineItemPtr = new QGraphicsLineItem( this );
        timeLineItemPtr->setVisible( false );
    }
    timeLineItemPtr->setZValue( 5 );
    // this->hide(); //�Ȳ���ʾ

    //��ʼ������գ��б�
    childrenItemPtrList.clear();
    childQGraphicsItemPtrList.clear();
}

TableColumn::~TableColumn() {
    // qDeleteAll( childrenItemPtrList );
}

void TableColumn::paint( QPainter *                      painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *                       widget ) {
    // QGraphicsRectItem::paint(painter, option, widget);
    backgroundItemPtr->paint( painter, option, widget );
    timeLineItemPtr->paint( painter, option, widget );
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->paint( painter, option, widget );
    }
}

void TableColumn::show() {
    // QGraphicsRectItem::show();
    backgroundItemPtr->show();
    timeLineItemPtr->show();
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->show();
    }
}

void TableColumn::hide() {
    // QGraphicsRectItem::hide();
    backgroundItemPtr->hide();
    timeLineItemPtr->hide();
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        itemPtr->hide();
    }
}

void TableColumn::resize( QResizeEvent *tableEvent ) {
    //�����Լ�
    QSize newSize = ClassTable::scaleSize( QSize( width, height ), tableEvent );
    width         = newSize.width();
    height        = newSize.height();
    ////width = parentTablePtr->width / parentTablePtr->getColumnNo();
    ////height = parentTablePtr->height;
    visibleWidth = width * 7 / 8;
    //��ΪҪ�ȳ�ʼ��width��height�����Ը��๹�캯��������ں���
    QGraphicsRectItem( getXPos(), getYPos(), width, height );

    //���±���
    QRectF originalRect = backgroundItemPtr->rect();
    QRectF newRect      = ClassTable::scaleSize( originalRect, tableEvent );
    backgroundItemPtr->setRect( newRect );
    ////backgroundItemPtr->setRect(getXPos(), 0, visibleWidth, height);
    //����ʱ����
    timeLineItemPtr->setLine(
        ClassTable::scaleSize( timeLineItemPtr->line(), tableEvent ) );
    /**
    QDateTime curDT     = QDateTime::currentDateTime();
    if (includeNow()) {
        timeLineItemPtr->setLine(getXPos(), itemYPosShouldBe( curDT ),
                             getXPos() + visibleWidth - timeLineWidth / 2,
    itemYPosShouldBe( curDT )); } else {

    }
    **/
}

void TableColumn::remove() {
    qDebug() << "\tRemoving TableColumn " << index << " {";
    QGraphicsScene *scenePtr = parentTablePtr->scenePtr;
    scenePtr->removeItem( backgroundItemPtr );
    scenePtr->removeItem( timeLineItemPtr );
    for ( QGraphicsTableItem *itemPtr : childQGraphicsItemPtrList ) {
        scenePtr->removeItem( itemPtr->textItemPtr );
        scenePtr->removeItem( itemPtr->backgroundItemPtr );
        scenePtr->removeItem( itemPtr );
        qDebug() << "\t\tRemoved QGraphicsTableItem "
                 << itemPtr->textItemPtr->toPlainText();
    }
    qDebug() << "\t} Removed TableColumn " << index;
}

/**
 * @brief   ������ʼʱ��
 * @warning ǰ�������ݳ�Աend�Ѿ���ʼ��
 * @todo
 */
void TableColumn::setStart( QDateTime st ) {
    if ( st < end )
        start = st;
}

/**
 * @brief   ���ý���ʱ��
 * @warning ǰ�������ݳ�Աstart�Ѿ���ʼ��
 * @todo
 */
void TableColumn::setEnd( QDateTime ed ) {
    if ( ed > start )
        end = ed;
}

int TableColumn::getXPos() const {
    int          xPos         = 0;
    QList< int > colIndexList = parentTablePtr->columnIndexList;
    for ( int listIndex = 0; listIndex < colIndexList.length(); ++listIndex ) {
        int colIndex = colIndexList[listIndex];
        if ( colIndex == this->index ) {
            break;
        }
        xPos += parentTablePtr->columnList[colIndex]->width;
    }
    return xPos;
}

int TableColumn::getYPos() const {
    return 0;
}

/**
 * @brief   ���ظ�TableColumn���ܳ��ȣ�����Ϊ��λ��
 */
qint64 TableColumn::getTimeLen() const {
    return start.secsTo( end );
}

/**
 * @brief   ����QDateTime����Y����
 * @note    static
 */
int TableColumn::itemYPosShouldBe( QDateTime itemStart, QDateTime colStart,
                                   QDateTime colEnd, int colHeight ) {
    return (int)( ( (qreal)colStart.secsTo( itemStart )
                    / (qreal)colStart.secsTo( colEnd ) )
                  * colHeight );   //��ʾold-style cast���ù�
}
/**
 * @overload
 * @note     non-static
 */
int TableColumn::itemYPosShouldBe( QDateTime itemStart ) const {
    return itemYPosShouldBe( itemStart, start, end, height );
}

bool TableColumn::includeNow() const {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return start <= currentDateTime && currentDateTime <= end;
}

void TableColumn::drawOnTable() const {
    qDebug() << "\tStart TableColumn " << index << " {";
    parentTablePtr->scenePtr->addItem( backgroundItemPtr );
    parentTablePtr->scenePtr->addItem( timeLineItemPtr );
    /**
   // ���Ƶ�ɫ����ǰʱ����
   QDateTime curDT     = QDateTime::currentDateTime();
   int       lineWidth = 3;
   if ( start <= curDT && curDT <= end ) {
       parentTablePtr->scenePtr->addRect( getXPos(), 0, visibleWidth, height,
                                          QPen( QColor( 0, 0, 0, 0 ) ),
                                          QBrush( QColor( 0, 0, 0, 100 ) ) );
       parentTablePtr->scenePtr->addLine(
           getXPos(), itemYPosShouldBe( curDT ),
           getXPos() + visibleWidth - lineWidth / 2, itemYPosShouldBe( curDT ),
           QPen( QBrush( Qt::red ), lineWidth ) );
   } else {
       parentTablePtr->scenePtr->addRect( getXPos(), 0, visibleWidth, height,
                                          QPen( QColor( 0, 0, 0, 0 ) ),
                                          QBrush( QColor( 0, 0, 0, 50 ) ) );
   }
   */
    // ����item
    for ( TableItem *childItemPtr : childrenItemPtrList ) {
        childItemPtr->drawOnTable( parentTablePtr->scenePtr );
    }
    qDebug() << "\t} Finish TableColumn " << index;
}
