#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#include "tableitem.h"

#include <QDate>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMainWindow>
#include <QString>

class TableColumn;
class ClassTableItem;

class ClassTable {
    friend class MainWindow;
    friend class SettingWindow;
    friend class TableColumn;
    friend class TableItem;
    friend class Subclass;
    friend class AddClassDialog;
    friend class SelectWeekDialog;
    friend class WeekButtonDelegate;

public:
    //构造函数
    explicit ClassTable( MainWindow *, QGraphicsView * );
    //析构函数
    ~ClassTable();

    //用于设置背景图片
    void setBackgroundImage( const QString filePath );

    int getColumnNo() const;

    void addItem( TableItem * );
    void addItem( ClassTableItem * );
    void draw() const;

    void           resize();
    static QSize   scaleSize( QSize smallOld, QResizeEvent *event );
    static QRectF  scaleSize( QRectF smallOld, QResizeEvent *event );
    static QLineF  scaleSize( QLineF smallOld, QResizeEvent *event );
    static QPointF scaleSize( QPointF smallOld, QResizeEvent *event );

protected:
    enum dayOfWeek {
        Monday = 1,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    //一周的起始日
    dayOfWeek    firstDayOfWeek;
    TableColumn *findColumn( dayOfWeek index ) const;

    //上级的MainWindow指针
    MainWindow *windowPtr;
    //包含的QGraphics家族指针
    QGraphicsView * viewPtr;
    QGraphicsScene *scenePtr;

    //背景图片的指针
    QGraphicsPixmapItem *backgroundImageItemPtr;
    QString              backgroundImageFilePath;

    //下级的TableColumn指针们
    QList< TableColumn * > columnList;
    //列TableColumn怎么排序（按照index），其长度即是列数
    QList< int > columnIndexList;

    //下级的TableItem指针们（注：考虑到一个TableItem可能出现在多个TableColumn中的情况）
    QList< TableItem * > classItemPtrList;

    //表格的宽度、高度
    int width, height;
    // TableItem的边框粗细
    int borderWidth = 10;

    QDate  termStartDate;
    quint8 termTotalWeek;

    //周数
    int          whichWeek( const QDate & = QDate::currentDate() ) const;
    static QDate sameWeek( const dayOfWeek day,
                           const QDate &   date       = QDate::currentDate(),
                           const int       weekOffset = 0 );

    void      setWeek( int week, QDate relativeDate );
    QDateTime start, end;
    int       weekOnTable;

    QList< QPair< QTime, QTime > > sectionTime;
};

#endif   // CLASSTABLE_H
