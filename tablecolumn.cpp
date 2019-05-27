#include "tablecolumn.h"


TableColumn::TableColumn( int index, QDateTime start, QDateTime end,
                          ClassTable *parent )
    : parentTablePtr( parent ), index( index ),
      width( parentTablePtr->width / parentTablePtr->getColumnNo() ),
      height( parentTablePtr->height ), visibleWidth( width - 10 ),
      start( start ), end( start <= end ? end : start ) {
    QGraphicsRectItem( getXPos(), getYPos(), width, height );

    //初始化（清空）列表
    childrenItemPtrList.clear();
}

TableColumn::~TableColumn() {
    qDeleteAll( childrenItemPtrList );
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
                  * colHeight );
}
/**
 * @overload
 * @note     non-static
 */
int TableColumn::itemYPosShouldBe( QDateTime itemStart ) const {
    return itemYPosShouldBe( itemStart, start, end, height );
}

void TableColumn::drawOnTable() const {
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
    // 绘制item
    for ( TableItem *childItemPtr : childrenItemPtrList ) {
        childItemPtr->drawOnTable( parentTablePtr->scenePtr );
    }
}
