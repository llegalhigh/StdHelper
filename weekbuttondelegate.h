#ifndef WEEKBUTTONDELEGATE_H
#define WEEKBUTTONDELEGATE_H

#include <QItemDelegate>

class WeekButtonDelegate : public QItemDelegate {
    Q_OBJECT

    friend class SelectWeekDialog;

public:
    WeekButtonDelegate( QObject *parent = nullptr );
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

private slots:
    void openDialog();
};

#endif   // WEEKBUTTONDELEGATE_H
