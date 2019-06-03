#include "classtable.h"

#include "classtableitem.h"
#include "mainwindow.h"
#include "tablecolumn.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsBlurEffect>

/**
 * @brief   ClassTable�Ĺ��캯��
 * @warning δ�ܱ���ʼ���ı����У�
 *              1. termStartDate, termTotalWeek, ...
 *                 ��Ҫͨ��SettingWindow����(PassAll)
 *              2. start, end, weekOnTable
 */
ClassTable::ClassTable( MainWindow *pw, QGraphicsView *pv )
    : firstDayOfWeek( Monday ), windowPtr( pw ), viewPtr( pv ),
      scenePtr( new QGraphicsScene() ),
      backgroundImageItemPtr( new QGraphicsPixmapItem() ),
      backgroundImageFilePath( ":/image/tableBackgroundImage" ),
      columnIndexList( { 1, 2, 3, 4, 5, 6, 7 } ) {
    //����view
    viewPtr->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    viewPtr->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff );   //��ֹ������
    viewPtr->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //��view����scene
    viewPtr->setScene( scenePtr );

    //�����Լ�
    width  = viewPtr->width();
    height = viewPtr->height();
    //���ӱ���ͼƬitem
    setBackgroundImage( backgroundImageFilePath );
    scenePtr->addItem( backgroundImageItemPtr );

    classItemPtrList.clear();

    sectionTime.clear();
    for ( int i = 0; i < 11; ++i ) {
        sectionTime.append( QPair< QTime, QTime >() );
    }
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    qDeleteAll( columnList );
    delete scenePtr;
}

void ClassTable::setBackgroundImage( const QString imagePath ) {
    //����λ��
    backgroundImageItemPtr->setPos( 0, 0 );
    backgroundImageItemPtr->setZValue( 0 );
    //����ͼ��
    QPixmap backgroundPixmap( imagePath );
    backgroundImageItemPtr->setPixmap( backgroundPixmap.scaled(
        width, height, Qt::KeepAspectRatioByExpanding ) );
    //ģ����
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

void ClassTable::addItem( ClassTableItem *classPtr ) {
    foreach ( Subclass subclass, classPtr->subclassList ) {
        for ( int week = 0; week < termTotalWeek; ++week ) {
            if ( subclass.isInWeek[week] ) {
                TableItem *item =
                    new TableItem( QString( "%1 @ %2" )
                                       .arg( classPtr->classAbbrName )
                                       .arg( subclass.place ),
                                   QDateTime( sameWeek( subclass.whichDayOfWeek,
                                                        termStartDate, week ),
                                              subclass.startTime ),
                                   QDateTime( sameWeek( subclass.whichDayOfWeek,
                                                        termStartDate, week ),
                                              subclass.endTime ),
                                   this );
                addItem( item );
            }
        }
    }
}

void ClassTable::draw() const {
    qDebug() << "Start ClassTable {";
    for ( TableColumn *colPtr : columnList ) {
        colPtr->drawOnTable();
    }
    qDebug() << "} Finish ClassTable";
}

/**
 * @brief   ��С���ı���¼�
 * @warning
 * @todo
 */
void ClassTable::resize() {
    //����oldSize
    int oldWidth  = width;
    int oldHeight = height;
    //�����Լ�
    width  = viewPtr->width();
    height = viewPtr->height();
    //����resize�¼�
    QSize         oldSize( oldWidth, oldHeight );
    QSize         newSize( width, height );
    QResizeEvent *tableEvent = new QResizeEvent( newSize, oldSize );

    //���±���ͼƬ
    setBackgroundImage( backgroundImageFilePath );
    //�ص㣺TableColumn��TableItem�໥�������ֱ����
    for ( TableColumn *colPtr : columnList ) {
        colPtr->resize( tableEvent );
    }
    for ( TableItem *itemPtr : classItemPtrList ) {
        itemPtr->resize( tableEvent );
    }

    delete tableEvent;
}

/**
 * @brief   ����ͼ�����죬���ڲ�������Ӧ��С
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

TableColumn *ClassTable::findColumn( ClassTable::dayOfWeek index ) const {
    for ( TableColumn *colPtr : columnList ) {
        if ( colPtr->index == index )
            return colPtr;
    }
    return nullptr;
}
/** scaleSize���ؽ��� */

/**
 * @brief   ����termStartDate������date�Ǳ�ѧ�ڵĵڼ���
 * @default dateĬ���ǵ�ǰ����
 */
int ClassTable::whichWeek( const QDate &date ) const {
    return ( date.year() - termStartDate.year() ) * 52
           + ( date.weekNumber() - termStartDate.weekNumber() ) + 1;
}

/**
 * @brief   ���غ�dateͬһ��(weekOffset=0)������day��Ӧ������
 * @warning ȷ��day��1~7֮��
 * @todo
 */
QDate ClassTable::sameWeek( const ClassTable::dayOfWeek day, const QDate &date,
                            const int weekOffset ) {
    return date.addDays( weekOffset * 7 + day - date.dayOfWeek() );
}

/**
 * @brief   ������ʾ(�����relativeDate��)��week��
 * @note    week=1��ͬһ��
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
        //���ڼ���ʱ��colIndex����
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