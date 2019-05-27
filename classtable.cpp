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
    //����view
    int windowWidth  = windowPtr->width();
    int windowHeight = windowPtr->getMainHeight();
    // viewPtr->setGeometry(0,0,windowWidth,windowHeight);
    /*
    viewPtr->setGeometry( 15, 15, windowPtr->width() * 4 / 5,
                          windowPtr->height() * 4 / 5 );
    */
    viewPtr->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    viewPtr->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff );   //��ֹ������
    viewPtr->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //����scene

    //��view����scene
    viewPtr->setScene( scenePtr );

    width  = windowWidth;
    height = windowHeight;

    //���ӱ���ͼƬitem
    backgroundImageFilePath = ":/image/tableBackgroundImage";
    setBackgroundImage( backgroundImageFilePath );
    scenePtr->addItem( backgroundImageItemPtr );

    //��ʼ��columnList
    columnList.clear();
    QDate currentDate = QDate::currentDate();
    int   colNum      = getColumnNo();
    for ( int listIndex = 0; listIndex < columnIndexList.length();
          ++listIndex ) {
        int colIndex = columnIndexList[listIndex];
        //���ڼ���ʱ��colIndex����
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
 * @brief   ��С���ı���¼�
 * @warning
 * @todo
 */
void ClassTable::resize() {
    //����oldSize
    int oldWidth  = width;
    int oldHeight = height;
    //�����Լ�
    width  = windowPtr->width();
    height = windowPtr->getMainHeight();
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
 * @brief   ����date�Ǳ�ѧ�ڵĵڼ���
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
