#include "classtableitem.h"

ClassTableItem::ClassTableItem( QString name, QString classAbbr,
                                QString teacherName, ClassTable *parentTable )
    : TableItem( "class" ), className( name ), classAbbrName( classAbbr ),
      teacherName( teacherName ) {
    subclassList.clear();
    parentTablePtr = parentTable;
}

void ClassTableItem::updateText() {
    text = QString( "%1 (%2)" ).arg( classAbbrName ).arg( teacherName );
}

void ClassTableItem::addSubclass( Subclass sub ) {
    sub.parentClassItem = this;
    subclassList.append( sub );
}
