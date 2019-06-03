#ifndef WEEKCOMBOBOXDELEGATE_H
#define WEEKCOMBOBOXDELEGATE_H

#include <QItemDelegate>

class WeekComboBoxDelegate : public QItemDelegate {
    Q_OBJECT

public:
    WeekComboBoxDelegate( QObject *parent = nullptr );
    QWidget *createEditor( QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const override;

    void setEditorData( QWidget *          editor,
                        const QModelIndex &index ) const override;
    void setModelData( QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index ) const override;

    void updateEditorGeometry( QWidget *                   editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index ) const override;
};

#endif   // WEEKCOMBOBOXDELEGATE_H
