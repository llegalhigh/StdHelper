#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QDateTime>
#include "classtable.h"
#include "tableitem.h"
#include <QList>

class TableColumn
{
public:
    //���캯����ָ��������ClassTable
    explicit TableColumn(ClassTable* = nullptr);
    //��������
    ~TableColumn();

    void setStart(QDateTime);
    void setEnd(QDateTime);

    //����
    void drawOnTable() const;

private:
    //�ϼ�ClassTable��ָ��
    ClassTable *parentTablePtr;
    //�¼�TableItem��ָ����
    QList<TableItem *> childrenItemPtrList;

    //�е����ƣ����硰���ڶ���
    QString name;
    //�еı�ţ�����2
    int index;
    //�еĿ�ȣ���ClassTable�Ŀ�ȼ���
    int width;

    //��һ���ϱ�Ե�����ʱ��
    QDateTime start;
    //�±�Ե�����ʱ��
    QDateTime end;
};

#endif // TABLECOLUMN_H
