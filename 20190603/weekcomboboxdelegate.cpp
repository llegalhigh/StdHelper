#include "weekcomboboxdelegate.h"

#include "classtable.h"

#include <QComboBox>

WeekComboBoxDelegate::WeekComboBoxDelegate( QObject *parent )
    : QItemDelegate( parent ) {}

QWidget *WeekComboBoxDelegate::createEditor( QWidget *                   parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index ) const {
    QComboBox *const comboBox = new QComboBox( parent );
    comboBox->addItem( tr( "Monday" ), 1 );
    comboBox->addItem( tr( "Tuesday" ), 2 );
    comboBox->addItem( tr( "Wednesday" ), 3 );
    comboBox->addItem( tr( "Thursday" ), 4 );
    comboBox->addItem( tr( "Friday" ), 5 );
    comboBox->addItem( tr( "Saturday" ), 6 );
    comboBox->addItem( tr( "Sunday" ), 7 );

    return comboBox;
}

void WeekComboBoxDelegate::setEditorData( QWidget *          editor,
                                          const QModelIndex &index ) const {
    QComboBox *const comboBox = qobject_cast< QComboBox * >( editor );
    Q_ASSERT( comboBox );

    const QString currentText = index.data( Qt::EditRole ).toString();
    const int     boxIndex    = comboBox->findText( currentText );
    if ( boxIndex >= 0 )
        comboBox->setCurrentIndex( boxIndex );
}

void WeekComboBoxDelegate::setModelData( QWidget *           editor,
                                         QAbstractItemModel *model,
                                         const QModelIndex & index ) const {
    QComboBox *const comboBox = qobject_cast< QComboBox * >( editor );
    Q_ASSERT( comboBox );

    model->setData( index, comboBox->currentText(), Qt::EditRole );
}

void WeekComboBoxDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex & ) const {
    editor->setGeometry( option.rect );
}
