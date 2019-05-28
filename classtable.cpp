#include "classtable.h"
#include "mainwindow.h"
#include "tablecolumn.h"
#include "ui_mainwindow.h"

#include <QDebug>


ClassTable::ClassTable( MainWindow *pw, QGraphicsView *pv )
    : firstDayOfWeek( Monday ), windowPtr( pw ), viewPtr( pv ),
      scenePtr( new QGraphicsScene() ),
      backgroundImageItemPtr( new QGraphicsPixmapItem() ),
      columnIndexList( { 1, 2, 3, 4, 5, 6, 7 } ) {
    //设置view
    int windowWidth  = windowPtr->width();
    int windowHeight = windowPtr->getMainHeight();
    // viewPtr->setGeometry(0,0,windowWidth,windowHeight);
    /*
    viewPtr->setGeometry( 15, 15, windowPtr->width() * 4 / 5,
                          windowPtr->height() * 4 / 5 );
    */
    viewPtr->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    viewPtr->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff );   //禁止滚动条
    viewPtr->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //设置scene

    //将view绑定至scene
    viewPtr->setScene( scenePtr );

    width  = windowWidth;
    height = windowHeight;

    //增加背景图片item
    backgroundImageFilePath = ":/image/tableBackgroundImage";
    setBackgroundImage( backgroundImageFilePath );
    scenePtr->addItem( backgroundImageItemPtr );

    //初始化columnList
    columnList.clear();
    QDate currentDate = QDate::currentDate();
    int   colNum      = getColumnNo();
    for ( int listIndex = 0; listIndex < columnIndexList.length();
          ++listIndex ) {
        int colIndex = columnIndexList[listIndex];
        //星期几暂时以colIndex代替
        QDate colDate = sameWeek( dayOfWeek( colIndex ), currentDate );
        // QDateTime startDT(colDate, QTime(0,0,0));
        // QDateTime endDT(colDate, QTime(23,59,59));
        QDateTime    startDT( colDate, QTime( 8, 0, 0 ) );
        QDateTime    endDT( colDate, QTime( 18, 0, 0 ) );
        TableColumn *colPtr = new TableColumn( colIndex, startDT, endDT, this,
                                               listIndex * width / colNum );
        columnList.append( colPtr );
    }
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    qDeleteAll( columnList );
    delete scenePtr;
}

void ClassTable::setBackgroundImage( const QString imagePath ) {
    backgroundImageItemPtr->setPos( 0, 0 );
    QPixmap backgroundPixmap( imagePath );
    backgroundImageItemPtr->setPixmap( backgroundPixmap.scaled(
        width, height, Qt::KeepAspectRatioByExpanding ) );
}

int ClassTable::getColumnNo() const {
    return columnIndexList.length();
}

void ClassTable::addItem( TableItem *itemPtr ) {
    classItemPtrList.append( itemPtr );
}

void ClassTable::draw() const {
    for ( TableColumn *colPtr : columnList ) {
        colPtr->drawOnTable();
    }
}

/**
 * @brief   大小被改变的事件
 * @warning
 * @todo
 */
void ClassTable::resize() {
    //储存oldSize
    int oldWidth  = width;
    int oldHeight = height;
    //更新自己
    width  = windowPtr->width();
    height = windowPtr->getMainHeight();
    //创建resize事件
    QSize         oldSize( oldWidth, oldHeight );
    QSize         newSize( width, height );
    QResizeEvent *tableEvent = new QResizeEvent( newSize, oldSize );

    //更新背景图片
    setBackgroundImage( backgroundImageFilePath );
    //重点：TableColumn和TableItem相互独立，分别更新
    for ( TableColumn *colPtr : columnList ) {
        colPtr->resize( tableEvent );
    }
    for ( TableItem *itemPtr : classItemPtrList ) {
        itemPtr->resize( tableEvent );
    }

    delete tableEvent;
}

QSize ClassTable::scaleSize( QSize smallOld, QResizeEvent *event ) {
    QSize bigNew( event->size() );
    QSize bigOld( event->oldSize() );
    return QSize( smallOld.width() * bigNew.width() / bigOld.width(),
                  smallOld.height() * bigNew.height() / bigOld.height() );
}

QRectF ClassTable::scaleSize( QRectF smallOld, QResizeEvent *event ) {
    QSize bigNew( event->size() );
    QSize bigOld( event->oldSize() );
    return QRectF( smallOld.x() * bigNew.width() / bigOld.width(),
                   smallOld.y() * bigNew.height() / bigOld.height(),
                   smallOld.width() * bigNew.width() / bigOld.width(),
                   smallOld.height() * bigNew.height() / bigOld.height() );
}

QLineF ClassTable::scaleSize( QLineF smallOld, QResizeEvent *event ) {
    QSize bigNew( event->size() );
    QSize bigOld( event->oldSize() );
    return QLineF( smallOld.x1() * bigNew.width() / bigOld.width(),
                   smallOld.y1() * bigNew.height() / bigOld.height(),
                   smallOld.x2() * bigNew.width() / bigOld.width(),
                   smallOld.y2() * bigNew.height() / bigOld.height() );
}

QPointF ClassTable::scaleSize( QPointF smallOld, QResizeEvent *event ) {
    QSize bigNew( event->size() );
    QSize bigOld( event->oldSize() );
    return QPointF( smallOld.x() * bigNew.width() / bigOld.width(),
                    smallOld.y() * bigNew.height() / bigOld.height() );
}

/**
 * @brief   返回date是本学期的第几周
 * @default date默认是当前日期
 */
int ClassTable::whichWeek( const QDate &date ) const {
    return ( date.year() - termStartDate.year() ) * 52
           + ( date.weekNumber() - termStartDate.weekNumber() ) + 1;
}

/**
 * @brief   返回和date同一周(weekOffset=0)的星期day对应的日期
 * @warning 确保day在1~7之间
 * @todo
 */
QDate ClassTable::sameWeek( const ClassTable::dayOfWeek day, const QDate &date,
                            const int weekOffset ) {
    return date.addDays( weekOffset * 7 + day - date.dayOfWeek() );
}
