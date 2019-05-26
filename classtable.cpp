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
    backgroundImageItemPtr->setPos( 0, 0 );
    scenePtr->addItem( backgroundImageItemPtr );
    setBackgroundImage( "D:/1.jpg" );

    columnList.clear();
    QDate currentDate = QDate::currentDate();
    for ( int colIndex : columnIndexList ) {
        //���ڼ���ʱ��colIndex����
        QDate colDate = sameWeek( dayOfWeek( colIndex ), currentDate );
        // QDateTime startDT(colDate, QTime(0,0,0));
        // QDateTime endDT(colDate, QTime(23,59,59));
        QDateTime    startDT( colDate, QTime( 8, 0, 0 ) );
        QDateTime    endDT( colDate, QTime( 18, 0, 0 ) );
        TableColumn *colPtr = new TableColumn( colIndex, startDT, endDT, this );
        columnList.append( colPtr );
    }
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    delete scenePtr;
}

void ClassTable::setBackgroundImage( const QString imagePath ) {
    QPixmap backgroundPixmap( imagePath );
    backgroundImageItemPtr->setPixmap(
        backgroundPixmap.scaled( width, height ) );
    backgroundImageItemPtr->show();
    // viewPtr->repaint();   //?
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
 * @todo    ��ûд�� 2019.5.26 23:29
 */
void ClassTable::resizeEvent() {
    width  = windowPtr->width();
    height = windowPtr->getMainHeight();
    for ( TableColumn *colPtr : columnList ) {
        colPtr->drawOnTable();
    }
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
