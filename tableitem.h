#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsItem>

class TableColumn;

class TableItem {

public:
    //���캯��
    explicit TableItem(const QString);
    explicit TableItem(const char *);
    //��������
    ~TableItem();

    //����
    void drawOnTable(QGraphicsScene *) const;

    void setText(const QString);
    QString getText() const;

private:
    //��ʾ������
    QString text;
};

#endif // TABLEITEM_H
