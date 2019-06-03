#include "weekbuttondelegate.h"

#include "selectweekdialog.h"

#include <QDebug>
#include <QPushButton>

WeekButtonDelegate::WeekButtonDelegate( QObject *   parent,
                                        MainWindow *mainWindowPtr )
    : QItemDelegate( parent ), mainWindowPtr( mainWindowPtr ),
      termTotalWeek( mainWindowPtr->childTablePtr->termTotalWeek ) {
    isInWeek.clear();
    for ( int i = 0; i < termTotalWeek; ++i ) {
        isInWeek.append( false );
    }
}

QWidget *WeekButtonDelegate::createEditor( QWidget *parent,
                                           const QStyleOptionViewItem &,
                                           const QModelIndex &index ) const {
    QWidget *const editor = new QWidget{ parent };
    setEditorData( parent, index );
    SelectWeekDialog *const dialog = new SelectWeekDialog(
        isInWeek, const_cast< WeekButtonDelegate * >( this ), editor );
    connect( dialog, &QDialog::accepted, this,
             &WeekButtonDelegate::commitAndCloseEditor );
    dialog->setWindowFlags( Qt::Window );
    dialog->setModal( true );
    dialog->show();
    return editor;
}

void WeekButtonDelegate::setEditorData( QWidget *,
                                        const QModelIndex &index ) const {
    const QString tableText = index.data( Qt::EditRole ).toString();
    if ( !tableText.isEmpty() ) {
        const QStringList boolStrList = tableText.split( "," );

        foreach ( QString boolStr, boolStrList ) {
            isInWeek[boolStr.toInt() - 1] = true;
        }
    }
}

void WeekButtonDelegate::setModelData( QWidget *, QAbstractItemModel *model,
                                       const QModelIndex &index ) const {
    QStringList boolStrList;
    for ( int i = 0; i < termTotalWeek; ++i ) {
        if ( isInWeek[i] ) {
            boolStrList.append( QString::number( i + 1 ) );
        }
    }
    model->setData( index, boolStrList.join( "," ), Qt::EditRole );
}

void WeekButtonDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex & ) const {
    editor->setGeometry( option.rect );
}

void WeekButtonDelegate::commitAndCloseEditor() {
    QWidget *editor = qobject_cast< QWidget * >( sender() );

    emit commitData( editor );
    emit closeEditor( editor );
}
