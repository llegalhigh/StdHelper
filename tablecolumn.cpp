#include "tablecolumn.h"


TableColumn::TableColumn( ClassTable *parent )
    : parentTablePtr( parent ),
      width( parentTablePtr->width
             / parentTablePtr->columnIndexList.length() ) {
    //初始化列表
    childrenItemPtrList.clear();
}

TableColumn::~TableColumn() {}

void TableColumn::setStart( QDateTime st ) {
    if ( st < end )
        start = st;
}

void TableColumn::setEnd( QDateTime ed ) {
    if ( ed > start )
        end = ed;
}

void TableColumn::drawOnTable() const {
    for ( TableItem *childItemPtr : childrenItemPtrList ) {
        childItemPtr->drawOnTable( parentTablePtr->scenePtr );
    }
}
