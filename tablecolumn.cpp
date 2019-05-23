#include "tablecolumn.h"

TableColumn::TableColumn(QDateTime st, QDateTime ed, ClassTable *parent)
    :parentTablePtr(parent)
{
    childrenItemPtrList.clear();
    setStart(st);
    setEnd(ed);
}

TableColumn::~TableColumn()
{

}

void TableColumn::setStart(QDateTime st)
{
    if(st<end)
        start = st;
}

void TableColumn::setEnd(QDateTime ed)
{
    if(ed>start)
        end = ed;
}
