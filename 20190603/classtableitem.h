#ifndef CLASSTABLEITEM_H
#define CLASSTABLEITEM_H

#include "subclass.h"
#include "tableitem.h"

#include <QString>

/**
 * @brief (����γ�������ͬ������ͬһ��ClassTableItem)
 */
class ClassTableItem : public TableItem {
    friend class AddClassDialog;
    friend class ClassTable;

public:
    ClassTableItem( QString name = "", QString classAbbr = "",
                    QString     teacherName = "",
                    ClassTable *parentTable = nullptr );

    void updateText();
    void addSubclass( Subclass sub );

protected:
    QString className     = "";   //�γ�ȫ�ƣ���"������������ͳ��"
    QString classAbbrName = "";   //�γ̼�ƣ���"������"
    QString teacherName   = "";   //��ʦ���ƣ���"������"
    QList< Subclass > subclassList;
};

#endif   // CLASSTABLEITEM_H
