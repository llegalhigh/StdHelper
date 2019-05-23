#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsItem>

class TableColumn;

class TableItem {

public:
    //构造函数
    explicit TableItem(const QString);
    explicit TableItem(const char *);
    //析构函数
    ~TableItem();

    //绘制
    void drawOnTable(QGraphicsScene *) const;

    void setText(const QString);
    QString getText() const;

private:
    //显示的文字
    QString text;
};

#endif // TABLEITEM_H
