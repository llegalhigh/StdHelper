#include "classtable.h"


ClassTable::ClassTable( QMainWindow *pw, QGraphicsView *pv )
    : firstDayOfWeek( Monday ), windowPtr( pw ), viewPtr( pv ),
      scenePtr( new QGraphicsScene() ),
      backgroundImageItemPtr( new QGraphicsPixmapItem() ),
      columnIndexList( { 1, 2, 3, 4, 5, 6, 7 } ), width( viewPtr->width() ),
      height( viewPtr->height() ) {
    viewPtr->setGeometry( 15, 15, windowPtr->width() * 4 / 5,
                          windowPtr->height() * 4 / 5 );
    viewPtr->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    //将view绑定至scene
    viewPtr->setScene( scenePtr );

    //增加背景图片item
    scenePtr->addItem( backgroundImageItemPtr );
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    delete scenePtr;
}

void ClassTable::setBackgroundImage( const QString imagePath ) {
    QPixmap backgroundPixmap( imagePath );
    backgroundImageItemPtr->setPixmap(
        backgroundPixmap.scaled( viewPtr->width(), viewPtr->height() ) );
    viewPtr->repaint();   //?
}

void ClassTable::addItem( TableItem *itemPtr ) {
    classItemPtrList.append( itemPtr );
}

void ClassTable::draw() const {
    foreach ( TableItem *itemPtr, classItemPtrList ) {
        itemPtr->drawOnTable( scenePtr );
    }
}

/**
 * @brief   返回date是本学期的第几周
 * @default date默认是当前日期
 */
int ClassTable::whichWeek( const QDate &date ) const {
    return ( date.year() - termStartDate.year() ) * 52
           + ( date.weekNumber() - termStartDate.weekNumber() );
}
