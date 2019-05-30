#include "tablecolumn.h"

#include <QDebug>


TableColumn::TableColumn( int index, QDateTime start, QDateTime end,
                          ClassTable *parent, int xPos )
    : parentTablePtr( parent ), index( index ),
      width( parentTablePtr->width / parentTablePtr->getColumnNo() ),
      height( parentTablePtr->height ), visibleWidth( width * 7 / 8 ),
      start( start ), end( start <= end ? end : start ) {
    //调用父类构造函数
    QGraphicsRectItem( xPos, getYPos(), width, height );
    //设置背景矩形
    bool includeNow = this->includeNow();
    backgroundItemPtr =
        new QGraphicsRectItem( xPos, 0, visibleWidth, height, this );
    backgroundItemPtr->setPen( QPen( QColor( 0, 0, 0, 0 ) ) );
    backgroundItemPtr->setBrush(
        QBrush( QColor( 0, 0, 0, includeNow ? 100 : 50 ) ) );
    backgroundItemPtr->setZValue( 1 );
    //设置时间线（如果有的话）
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
    // this->hide(); //先不显示

    //初始化（清空）列表
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
    //更新自己
    QSize newSize = ClassTable::scaleSize( QSize( width, height ), tableEvent );
    width         = newSize.width();
    height        = newSize.height();
    ////width = parentTablePtr->width / parentTablePtr->getColumnNo();
    ////height = parentTablePtr->height;
    visibleWidth = width * 7 / 8;
    //因为要先初始化width和height，所以父类构造函数必须放在后面
    QGraphicsRectItem( getXPos(), getYPos(), width, height );

    //更新背景
    QRectF originalRect = backgroundItemPtr->rect();
    QRectF newRect      = ClassTable::scaleSize( originalRect, tableEvent );
    backgroundItemPtr->setRect( newRect );
    ////backgroundItemPtr->setRect(getXPos(), 0, visibleWidth, height);
    //更新时间线
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
 * @brief   设置起始时间
 * @warning 前提是数据成员end已经初始化
 * @todo
 */
void TableColumn::setStart( QDateTime st ) {
    if ( st < end )
        start = st;
}

/**
 * @brief   设置结束时间
 * @warning 前提是数据成员start已经初始化
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
 * @brief   返回该TableColumn的总长度（以秒为单位）
 */
qint64 TableColumn::getTimeLen() const {
    return start.secsTo( end );
}

/**
 * @brief   给定QDateTime推算Y坐标
 * @note    static
 */
int TableColumn::itemYPosShouldBe( QDateTime itemStart, QDateTime colStart,
                                   QDateTime colEnd, int colHeight ) {
    return (int)( ( (qreal)colStart.secsTo( itemStart )
                    / (qreal)colStart.secsTo( colEnd ) )
                  * colHeight );   //提示old-style cast不用管
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
   // 绘制底色、当前时间线
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
    // 绘制item
    for ( TableItem *childItemPtr : childrenItemPtrList ) {
        childItemPtr->drawOnTable( parentTablePtr->scenePtr );
    }
    qDebug() << "\t} Finish TableColumn " << index;
}
