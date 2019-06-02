#include "sectionscomboboxdelegate.h"

#include "sectionscombobox.h"
#include "ui_sectionscombobox.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextStream>

SectionsComboBoxDelegate::SectionsComboBoxDelegate( QObject *parent )
    : QItemDelegate( parent ) {}

QWidget *
SectionsComboBoxDelegate::createEditor( QWidget *                   parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index ) const {
    SectionsComboBox *const box = new SectionsComboBox( parent );
    return box;
    /*
    QWidget *const boxes = new QWidget( parent );
    boxes->setGeometry( option.rect );
    QHBoxLayout *const layout = new QHBoxLayout( boxes );

    QComboBox *const start = new QComboBox( boxes );
    QLabel *const    to    = new QLabel( "~", boxes );
    QComboBox *const end   = new QComboBox( boxes );
    layout->addWidget( start );
    layout->addWidget( to );
    layout->addWidget( end );

    for ( int i = 1; i <= 12; ++i ) {
        start->addItem( QString::number( i ), i );
    }
    start->setCurrentIndex( 0 );
    for ( int j = start->currentIndex() + 1; j <= 12; ++j )
        end->addItem( QString::number( j ), j );
    end->setCurrentIndex( 0 );

    boxes->setLayout( layout );
    return boxes;
*/
}

void SectionsComboBoxDelegate::setEditorData( QWidget *          editor,
                                              const QModelIndex &index ) const {
    SectionsComboBox *const box = qobject_cast< SectionsComboBox * >( editor );
    /*
    QComboBox *const start
        qobject_cast< QComboBox * >( editor->layout()->itemAt( 0 )->widget() );
    QComboBox *const end =
        qobject_cast< QComboBox * >( editor->layout()->itemAt( 2 )->widget() );
    */
    QString     str = index.data( Qt::EditRole ).toString();
    QTextStream read( &str );
    int         startInt, endInt;
    char        tilde;
    read >> startInt >> tilde >> endInt;
    box->ui->startBox->setCurrentText( QString::number( startInt ) );
    box->ui->endBox->setCurrentText( QString::number( endInt ) );
}

void SectionsComboBoxDelegate::setModelData( QWidget *           editor,
                                             QAbstractItemModel *model,
                                             const QModelIndex & index ) const {
    SectionsComboBox *const box = qobject_cast< SectionsComboBox * >( editor );
    model->setData( index,
                    box->ui->startBox->currentText().append( '~' ).append(
                        box->ui->endBox->currentText() ),
                    Qt::EditRole );
}

void SectionsComboBoxDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index ) const {
    editor->setGeometry( option.rect );
}
