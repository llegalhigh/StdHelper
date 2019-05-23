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
public:
    //构造函数
    explicit ClassTable(QMainWindow*, QGraphicsView*);
    //析构函数
    ~ClassTable();

    //用于设置背景图片
    void setBackgroundImage(const QString);

    void addItem(TableItem *);
    void draw() const;

private:
    enum dayOfWeek {
        Monday=1,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    dayOfWeek firstDayOfWeek;

    QMainWindow *windowPtr;
    QGraphicsView *viewPtr;
    QGraphicsScene *scenePtr;

    QGraphicsPixmapItem *backgroundImageItemPtr;

    QList<TableItem *> classItemPtrList;
};

#endif // CLASSTABLE_H
