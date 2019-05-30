#include "classtable.h"
#include "mainwindow.h"
#include "tablecolumn.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsBlurEffect>


/**
 * @brief   ClassTable的构造函数
 * @warning 未能被初始化的变量有：
 *              1. termStartDate, termTotalWeek, ...
 *                 需要通过SettingWindow传递(PassAll)
 *              2. start, end, weekOnTable
 */
ClassTable::ClassTable( MainWindow *pw, QGraphicsView *pv )
    : firstDayOfWeek( Monday ), windowPtr( pw ), viewPtr( pv ),
      scenePtr( new QGraphicsScene() ),
      backgroundImageItemPtr( new QGraphicsPixmapItem() ),
      backgroundImageFilePath( ":/image/tableBackgroundImage" ),
      columnIndexList( { 1, 2, 3, 4, 5, 6, 7 } ) {
    //设置view
    viewPtr->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    viewPtr->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff );   //禁止滚动条
    viewPtr->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //将view绑定至scene
    viewPtr->setScene( scenePtr );

    //设置自己
    width  = viewPtr->width();
    height = viewPtr->height();
    //增加背景图片item
    setBackgroundImage( backgroundImageFilePath );
    scenePtr->addItem( backgroundImageItemPtr );

    //默认初始显示当前周
    // setWeek(1, QDate::currentDate());

    classItemPtrList.clear();
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    qDeleteAll( columnList );
    delete scenePtr;
}

void ClassTable::setBackgroundImage( const QString imagePath ) {
    //调整位置
    backgroundImageItemPtr->setPos( 0, 0 );
    backgroundImageItemPtr->setZValue( 0 );
    //设置图像
    QPixmap backgroundPixmap( imagePath );
    backgroundImageItemPtr->setPixmap( backgroundPixmap.scaled(
        width, height, Qt::KeepAspectRatioByExpanding ) );
    //模糊化
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
    effect->setBlurRadius( 5 );
    backgroundImageItemPtr->setGraphicsEffect( effect );
}

int ClassTable::getColumnNo() const {
    return columnIndexList.length();
}

void ClassTable::addItem( TableItem *itemPtr ) {
    classItemPtrList.append( itemPtr );
    itemPtr->parentTablePtr = this;
}

void ClassTable::draw() const {
    qDebug() << "Start ClassTable {";
    for ( TableColumn *colPtr : columnList ) {
        colPtr->drawOnTable();
    }
    qDebug() << "} Finish ClassTable";
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
    width  = viewPtr->width();
    height = viewPtr->height();
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

/**
 * @brief   计算图形拉伸，用于部件自适应大小
 */
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
/** scaleSize重载结束 */

/**
 * @brief   根据termStartDate，计算date是本学期的第几周
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

/**
 * @brief   设置显示(相对于relativeDate的)第week周
 * @note    week=1是同一周
 */
void ClassTable::setWeek( int week, QDate relativeDate ) {
    for ( TableColumn *colPtr : columnList ) {
        colPtr->remove();
    }
    columnList.clear();

    weekOnTable = week;
    start       = QDateTime( sameWeek( Monday, relativeDate, week - 1 ),
                       QTime( 0, 0, 0 ) );
    end         = QDateTime( sameWeek( Sunday, relativeDate, week - 1 ),
                     QTime( 0, 0, 0 ) );
    for ( int listIndex = 0; listIndex < columnIndexList.length();
          ++listIndex ) {
        int colIndex = columnIndexList[listIndex];
        //星期几暂时以colIndex代替
        QDate colDate =
            sameWeek( dayOfWeek( colIndex ), relativeDate, week - 1 );
        QDateTime    startDT( colDate, QTime( 0, 0, 0 ) );
        QDateTime    endDT( colDate, QTime( 23, 59, 59 ) );
        int          colNum = getColumnNo();
        TableColumn *colPtr = new TableColumn( colIndex, startDT, endDT, this,
                                               listIndex * width / colNum );
        columnList.append( colPtr );
    }

    for ( TableItem *itemPtr : classItemPtrList ) {
        itemPtr->findParentColumns();
    }
}
