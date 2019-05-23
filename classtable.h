#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QMainWindow>
#include "tableitem.h"

class ClassTable
{
    friend TableColumn;

public:
    //构造函数
    explicit ClassTable(QMainWindow*, QGraphicsView*);
    //析构函数
    ~ClassTable();

    //用于设置背景图片
    void setBackgroundImage(const QString);

    void addItem(TableItem *);
    void draw() const;

protected:
    enum dayOfWeek {
        Monday=1,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    //一周的起始日
    dayOfWeek firstDayOfWeek;

    //各种指针
    QMainWindow *windowPtr;
    QGraphicsView *viewPtr;
    QGraphicsScene *scenePtr;

    QGraphicsPixmapItem *backgroundImageItemPtr;

    QList<TableItem *> classItemPtrList;

    //列TableColumn怎么排序（按照index）
    QList<int> columnIndexList;
    //表格的宽度
    int width;
};

#endif // CLASSTABLE_H
