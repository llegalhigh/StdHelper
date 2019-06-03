#ifndef QGRAPHICSTABLEITEM_H
#define QGRAPHICSTABLEITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QResizeEvent>


class TableColumn;

class QGraphicsTableItem : public QGraphicsRectItem {
    friend class TableItem;
    friend class TableColumn;

public:
    explicit QGraphicsTableItem(
        TableColumn *parentCol = nullptr, TableItem *parentItem = nullptr,
        int xPos = 0, int yPos = 0, int width = 0, int height = 0,
        QPen    borderPen = QPen( QBrush( Qt::white ), 5 ),
        QBrush  fillBrush = QBrush( QColor( 0, 0, 255, 100 ) ),
        QString text = "", QColor textColor = Qt::white,
        QFont textFont = QFont( "Helvetica", 10, QFont::Bold, false ) );

    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget = nullptr ) override;
    void show();
    void hide();
    void resize( QResizeEvent *tableEvent );
    void resize( int xPos, int yPos, int width, int height );

protected:
    TableColumn *parentColumnPtr;
    TableItem *  parentItemPtr;

    QGraphicsRectItem *backgroundItemPtr;
    QGraphicsTextItem *textItemPtr;
};

#endif   // QGRAPHICSTABLEITEM_H
