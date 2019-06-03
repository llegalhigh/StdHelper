#ifndef WEEKBUTTONDELEGATE_H
#define WEEKBUTTONDELEGATE_H

#include "mainwindow.h"

#include <QItemDelegate>

class WeekButtonDelegate : public QItemDelegate {
    Q_OBJECT

    friend class SelectWeekDialog;

public:
    WeekButtonDelegate( QObject *   parent        = nullptr,
                        MainWindow *mainWindowPtr = nullptr );
    QWidget *createEditor( QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const override;

    void setEditorData( QWidget *          editor,
                        const QModelIndex &index ) const override;
    void setModelData( QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index ) const override;

    void updateEditorGeometry( QWidget *                   editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index ) const override;

protected:
    mutable QList< bool > isInWeek;
    MainWindow *          mainWindowPtr;
    int                   termTotalWeek;

private slots:
    void commitAndCloseEditor();
};

#endif   // WEEKBUTTONDELEGATE_H
