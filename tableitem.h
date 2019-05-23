#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsItem>

class TableItem {

public:
    explicit TableItem(const QString);
    explicit TableItem(const char *);

    ~TableItem();

    void drawOnTable(QGraphicsScene *) const;

    void setText(const QString);
    QString getText() const;

private:
    QString text;
};

#endif // TABLEITEM_H
