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

class ClassTable {
    friend class MainWindow;
    friend class SettingWindow;
    friend class TableColumn;
    friend class TableItem;

public:
    //构造函数
    explicit ClassTable( MainWindow *, QGraphicsView * );
    //析构函数
    ~ClassTable();

    //用于设置背景图片
    void setBackgroundImage( const QString );

    int getColumnNo() const;

    void addItem( TableItem * );
    void draw() const;

    void resizeEvent();

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
    dayOfWeek firstDayOfWeek;

    //上级的MainWindow指针
    MainWindow *windowPtr;
    //包含的QGraphics家族指针
    QGraphicsView * viewPtr;
    QGraphicsScene *scenePtr;

    //背景图片的指针
    QGraphicsPixmapItem *backgroundImageItemPtr;

    //下级的TableColumn指针们
    QList< TableColumn * > columnList;
    //列TableColumn怎么排序（按照index），其长度即是列数
    QList< int > columnIndexList;

    //下级的TableItem指针们（注：考虑到一个TableItem可能出现在多个TableColumn中的情况）
    QList< TableItem * > classItemPtrList;

    //表格的宽度、高度
    int width, height;
    // TableItem的宽度
    int borderWidth = 10;

    QDate  termStartDate;
    quint8 termTotalWeek;

    int          whichWeek( const QDate & = QDate::currentDate() ) const;
    static QDate sameWeek( const dayOfWeek day,
                           const QDate &   date       = QDate::currentDate(),
                           const int       weekOffset = 0 );
};

#endif   // CLASSTABLE_H
