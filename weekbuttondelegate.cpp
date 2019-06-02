#include "weekbuttondelegate.h"

#include "selectweekdialog.h"

#include <QDebug>
#include <QPushButton>

WeekButtonDelegate::WeekButtonDelegate( QObject *parent )
    : QItemDelegate( parent ) {
    isInWeek.clear();
    for ( int i = 0; i < 20; ++i ) {
        isInWeek.append( false );
    }
}

QWidget *WeekButtonDelegate::createEditor( QWidget *parent,
                                           const QStyleOptionViewItem &,
                                           const QModelIndex & ) const {
    QPushButton *const button = new QPushButton( "Edit", parent );
    button->setFocusPolicy( Qt::StrongFocus );
    connect( button, SIGNAL( clicked() ), this, SLOT( openDialog() ) );
    return button;
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

    /*
    QPushButton *const button = qobject_cast< QPushButton * >( editor );
    Q_ASSERT( button );

    const QString currentText = index.data( Qt::EditRole ).toString();
    button->setText( currentText );
    */
}

void WeekButtonDelegate::setModelData( QWidget *, QAbstractItemModel *model,
                                       const QModelIndex &index ) const {
    QStringList boolStrList;
    for ( int i = 0; i < 20; ++i ) {
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

void WeekButtonDelegate::openDialog() {
    SelectWeekDialog *dialog = new SelectWeekDialog( isInWeek, this );
    dialog->exec();
}
