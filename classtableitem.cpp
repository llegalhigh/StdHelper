#include "classtableitem.h"

ClassTableItem::ClassTableItem() {
    subclassList.clear();
}

ClassTableItem::ClassTableItem( QString name, QString classAbbr,
                                QString teacherName, ClassTable *parentTable )
    : className( name ), classAbbrName( classAbbr ),
      teacherName( teacherName ) {
    subclassList.clear();
    parentTablePtr = parentTable;
}

void ClassTableItem::updateText() {
    text = QString( classAbbrName )
               .append( " (" )
               .append( teacherName )
               .append( ")" );
}

void ClassTableItem::addSubclass( Subclass sub ) {
    sub.parentClassItem = this;
    subclassList.append( sub );
}
