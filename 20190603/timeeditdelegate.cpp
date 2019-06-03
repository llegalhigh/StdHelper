#include "timeeditdelegate.h"

#include <QTimeEdit>

TimeEditDelegate::TimeEditDelegate( QObject *parent )
    : QItemDelegate( parent ) {}

QWidget *TimeEditDelegate::createEditor( QWidget *                   parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index ) const {
    QTimeEdit *const timeEdit = new QTimeEdit( parent );
    return timeEdit;
}

void TimeEditDelegate::setEditorData( QWidget *          editor,
                                      const QModelIndex &index ) const {
    QTimeEdit *const timeEdit = qobject_cast< QTimeEdit * >( editor );
    Q_ASSERT( timeEdit );

    const QStringList tableStringList =
        index.data( Qt::EditRole ).toString().split( ":" );
    const QTime tableTime{ tableStringList[0].toInt(),
                           tableStringList[1].toInt() };
    timeEdit->setTime( tableTime );
}

void TimeEditDelegate::setModelData( QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index ) const {
    QTimeEdit *const timeEdit = qobject_cast< QTimeEdit * >( editor );
    Q_ASSERT( timeEdit );

    model->setData( index, timeEdit->time(), Qt::EditRole );
}

void TimeEditDelegate::updateEditorGeometry( QWidget *                   editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex & ) const {
    editor->setGeometry( option.rect );
}
