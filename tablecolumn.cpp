#include "tablecolumn.h"


TableColumn::TableColumn( int index, QDateTime start, QDateTime end,
                          ClassTable *parent )
    : parentTablePtr( parent ), index( index ),
      width( parentTablePtr->width / parentTablePtr->getColumnNo() ),
      height( parentTablePtr->height ), visibleWidth( width - 10 ),
      start( start ), end( start <= end ? end : start ) {
    QGraphicsRectItem( getXPos(), getYPos(), width, height );

    //��ʼ������գ��б�
    childrenItemPtrList.clear();
}

TableColumn::~TableColumn() {
    qDeleteAll( childrenItemPtrList );
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
    // ����item
    for ( TableItem *childItemPtr : childrenItemPtrList ) {
        childItemPtr->drawOnTable( parentTablePtr->scenePtr );
    }
}
