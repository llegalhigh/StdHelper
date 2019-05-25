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


class ClassTable {
    friend class MainWindow;
    friend class SettingWindow;
    friend class TableColumn;

public:
    //���캯��
    explicit ClassTable( QMainWindow *, QGraphicsView * );
    //��������
    ~ClassTable();

    //�������ñ���ͼƬ
    void setBackgroundImage( const QString );

    void addItem( TableItem * );
    void draw() const;

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
    //һ�ܵ���ʼ��
    dayOfWeek firstDayOfWeek;

    //����ָ��
    QMainWindow *   windowPtr;
    QGraphicsView * viewPtr;
    QGraphicsScene *scenePtr;

    QGraphicsPixmapItem *backgroundImageItemPtr;

    QList< TableItem * > classItemPtrList;

    //��TableColumn��ô���򣨰���index��
    QList< int > columnIndexList;
    //���Ŀ�ȡ��߶�
    int width, height;

    QDate  termStartDate;
    quint8 termTotalWeek;

    int whichWeek( const QDate & = QDate::currentDate() ) const;
};

#endif   // CLASSTABLE_H
