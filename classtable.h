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
    //���캯��
    explicit ClassTable( MainWindow *, QGraphicsView * );
    //��������
    ~ClassTable();

    //�������ñ���ͼƬ
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
    //һ�ܵ���ʼ��
    dayOfWeek firstDayOfWeek;

    //�ϼ���MainWindowָ��
    MainWindow *windowPtr;
    //������QGraphics����ָ��
    QGraphicsView * viewPtr;
    QGraphicsScene *scenePtr;

    //����ͼƬ��ָ��
    QGraphicsPixmapItem *backgroundImageItemPtr;

    //�¼���TableColumnָ����
    QList< TableColumn * > columnList;
    //��TableColumn��ô���򣨰���index�����䳤�ȼ�������
    QList< int > columnIndexList;

    //�¼���TableItemָ���ǣ�ע�����ǵ�һ��TableItem���ܳ����ڶ��TableColumn�е������
    QList< TableItem * > classItemPtrList;

    //���Ŀ�ȡ��߶�
    int width, height;
    // TableItem�Ŀ��
    int borderWidth = 10;

    QDate  termStartDate;
    quint8 termTotalWeek;

    int          whichWeek( const QDate & = QDate::currentDate() ) const;
    static QDate sameWeek( const dayOfWeek day,
                           const QDate &   date       = QDate::currentDate(),
                           const int       weekOffset = 0 );
};

#endif   // CLASSTABLE_H
