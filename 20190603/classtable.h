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
    //���캯��
    explicit ClassTable( MainWindow *, QGraphicsView * );
    //��������
    ~ClassTable();

    //�������ñ���ͼƬ
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
    //һ�ܵ���ʼ��
    dayOfWeek    firstDayOfWeek;
    TableColumn *findColumn( dayOfWeek index ) const;

    //�ϼ���MainWindowָ��
    MainWindow *windowPtr;
    //������QGraphics����ָ��
    QGraphicsView * viewPtr;
    QGraphicsScene *scenePtr;

    //����ͼƬ��ָ��
    QGraphicsPixmapItem *backgroundImageItemPtr;
    QString              backgroundImageFilePath;

    //�¼���TableColumnָ����
    QList< TableColumn * > columnList;
    //��TableColumn��ô���򣨰���index�����䳤�ȼ�������
    QList< int > columnIndexList;

    //�¼���TableItemָ���ǣ�ע�����ǵ�һ��TableItem���ܳ����ڶ��TableColumn�е������
    QList< TableItem * > classItemPtrList;

    //���Ŀ�ȡ��߶�
    int width, height;
    // TableItem�ı߿��ϸ
    int borderWidth = 10;

    QDate  termStartDate;
    quint8 termTotalWeek;

    //����
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
