#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include "classtable.h"
#include "tableitem.h"

#include <QDateTime>
#include <QGraphicsRectItem>
#include <QList>


class TableColumn : public QGraphicsRectItem {
    friend class ClassTable;
    friend class TableItem;

public:
    //���캯����ָ��������ClassTable
    TableColumn( int, QDateTime, QDateTime, ClassTable * = nullptr );
    //��������
    ~TableColumn();

    void setStart( QDateTime );
    void setEnd( QDateTime );

    int    getXPos() const;
    int    getYPos() const;
    qint64 getTimeLen() const;

    static int itemYPosShouldBe( QDateTime itemStart, QDateTime colStart,
                                 QDateTime colEnd, int colHeight );
    int        itemYPosShouldBe( QDateTime itemStart ) const;

    //����
    void drawOnTable() const;

protected:
    //�ϼ�ClassTable��ָ��
    ClassTable *parentTablePtr;
    //�¼�TableItem��ָ����
    QList< TableItem * > childrenItemPtrList;

    //�е����ƣ����硰���ڶ���
    QString name;
    //�еı�ţ�����2
    int index;
    //�еĿ�ȡ��߶ȣ�����ClassTable�ļ���
    int width, height;
    int visibleWidth;

    //��һ���ϱ�Ե�����ʱ�䣬����5��25��00:00:00
    QDateTime start;
    //�±�Ե�����ʱ�䣬����5��25��23:59:59
    QDateTime end;
};

#endif   // TABLECOLUMN_H
