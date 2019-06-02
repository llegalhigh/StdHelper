#ifndef SECTIONSCOMBOBOXDELEGATE_H
#define SECTIONSCOMBOBOXDELEGATE_H

#include <QItemDelegate>

class SectionsComboBoxDelegate : public QItemDelegate {
public:
    SectionsComboBoxDelegate( QObject *parent = nullptr );
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

#endif   // SECTIONSCOMBOBOXDELEGATE_H
