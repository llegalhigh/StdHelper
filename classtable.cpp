#include "classtable.h"

ClassTable::ClassTable(QMainWindow *pw, QGraphicsView *pv)
    : firstDayOfWeek(Monday),
      windowPtr(pw),viewPtr(pv), scenePtr(new QGraphicsScene()), backgroundImageItemPtr(new QGraphicsPixmapItem()),
      columnIndexList({1,2,3,4,5,6,7}),
      width(viewPtr->width())
{
    viewPtr->setGeometry(15,15,windowPtr->width()*4/5,windowPtr->height()*4/5);
    viewPtr->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    //将view绑定至scene
    viewPtr->setScene(scenePtr);

    //增加背景图片item
    scenePtr->addItem(backgroundImageItemPtr);
}

ClassTable::~ClassTable() {
    delete backgroundImageItemPtr;
    delete scenePtr;
}

void ClassTable::setBackgroundImage(const QString imagePath)
{
    QPixmap backgroundPixmap(imagePath);
    backgroundImageItemPtr->setPixmap(backgroundPixmap.scaled(viewPtr->width(),viewPtr->height()));
    viewPtr->repaint();//?
}

void ClassTable::addItem(TableItem *itemPtr)
{
    classItemPtrList.append(itemPtr);
}

void ClassTable::draw() const
{
    foreach (TableItem *itemPtr, classItemPtrList) {
        itemPtr->drawOnTable(scenePtr);
    }
}
