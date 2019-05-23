#include "tableitem.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>

TableItem::TableItem(const QString itemText) {
    setText(itemText);
}

TableItem::TableItem(const char *string) {
    setText(QString::fromLocal8Bit(string));
}

void TableItem::drawOnTable(QGraphicsScene *scene) const {
    // ���ñ߿�͵�ɫ
    QPen *borderPenPtr=new QPen(QBrush(Qt::white),10);
    borderPenPtr->setJoinStyle(Qt::RoundJoin);

    // ��������
    QGraphicsTextItem *textItemPtr=new QGraphicsTextItem();
    textItemPtr->setPlainText(this->text);
    textItemPtr->setDefaultTextColor(Qt::white);
    textItemPtr->setPos(60,60);
    textItemPtr->setTextWidth(90);
    QFont textFont;
    textFont.setBold(true);
    textFont.setPointSize(15);
    textItemPtr->setFont(textFont);

    // ���Ƶ�scene��
    scene->addRect(50,50,100,400, *borderPenPtr,QBrush(QColor(0,0,255,100)));
    scene->addItem(textItemPtr);
}

void TableItem::setText(const QString text) {
    this->text = text;
}
