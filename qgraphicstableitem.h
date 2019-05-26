#ifndef QGRAPHICSTABLEITEM_H
#define QGRAPHICSTABLEITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>


class TableColumn;

class QGraphicsTableItem : public QGraphicsRectItem {
    friend class TableItem;

public:
    explicit QGraphicsTableItem(
        TableColumn *parentCol = nullptr, int xPos = 0, int yPos = 0,
        int width = 0, int height = 0,
        QPen    borderPen = QPen( QBrush( Qt::white ), 5 ),
        QBrush  fillBrush = QBrush( QColor( 0, 0, 255, 100 ) ),
        QString text = "", QColor textColor = Qt::white,
        QFont textFont = QFont( "Helvetica", 10, QFont::Bold, false ) );

    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget = nullptr ) override;

protected:
    TableColumn *parentColumnPtr;

    QGraphicsRectItem *backgroundItemPtr;
    QGraphicsTextItem *textItemPtr;
};

#endif   // QGRAPHICSTABLEITEM_H
