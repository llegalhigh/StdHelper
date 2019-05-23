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
    //���캯��
    explicit ClassTable(QMainWindow*, QGraphicsView*);
    //��������
    ~ClassTable();

    //�������ñ���ͼƬ
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
    //һ�ܵ���ʼ��
    dayOfWeek firstDayOfWeek;

    //����ָ��
    QMainWindow *windowPtr;
    QGraphicsView *viewPtr;
    QGraphicsScene *scenePtr;

    QGraphicsPixmapItem *backgroundImageItemPtr;

    QList<TableItem *> classItemPtrList;

    //��TableColumn��ô���򣨰���index��
    QList<int> columnIndexList;
    //���Ŀ��
    int width;
};

#endif // CLASSTABLE_H
