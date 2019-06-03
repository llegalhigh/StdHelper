#include "subclass.h"

#include "classtableitem.h"

Subclass::Subclass( ClassTable::dayOfWeek whichDay, QTime start, QTime end,
                    QString place )
    : whichDayOfWeek( whichDay ), place( place ), startTime( start ),
      endTime( end ) {
    qItem = new QGraphicsTableItem(
        parentClassItem->parentTablePtr->findColumn( whichDay ),
        parentClassItem );
    parentClassItem->findParentColumns();

    isInWeek.clear();
    for ( int i = 0; i < parentClassItem->parentTablePtr->termTotalWeek; ++i ) {
        isInWeek.append( false );
    }
}
