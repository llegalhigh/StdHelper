#ifndef CLASSTABLEITEM_H
#define CLASSTABLEITEM_H

#include "subclass.h"
#include "tableitem.h"

#include <QString>

/**
 * @brief (概念，课程名称相同就算做同一个ClassTableItem)
 */
class ClassTableItem : public TableItem {
public:
    ClassTableItem();
    ClassTableItem( QString name, QString classAbbr, QString teacherName,
                    ClassTable *parentTable = nullptr );

    void updateText();
    void addSubclass( Subclass sub );

protected:
    QString className     = "";   //课程全称，如"概率论与数理统计"
    QString classAbbrName = "";   //课程简称，如"概率论"
    QString teacherName   = "";   //教师名称，如"蔡吴兴"
    QList< Subclass > subclassList;
};

#endif   // CLASSTABLEITEM_H
