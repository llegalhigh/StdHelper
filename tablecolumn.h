#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include "classtable.h"
#include "tableitem.h"
#include <QDateTime>
#include <QList>

class TableColumn {
public:
    //���캯����ָ��������ClassTable
    explicit TableColumn(ClassTable * = nullptr);
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
    //�еĿ�ȡ��߶ȣ���ClassTable�ļ���
    int width, height;

    //��һ���ϱ�Ե�����ʱ��
    QDateTime start;
    //�±�Ե�����ʱ��
    QDateTime end;
};

#endif // TABLECOLUMN_H
