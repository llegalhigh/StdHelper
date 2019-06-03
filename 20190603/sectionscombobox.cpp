#include "sectionscombobox.h"

#include "ui_sectionscombobox.h"

#include <QDebug>

SectionsComboBox::SectionsComboBox( QWidget *parent )
    : QWidget( parent ), ui( new Ui::SectionsComboBox ) {
    ui->setupUi( this );
    for ( int i = 1; i <= 12; ++i ) {
        ui->startBox->addItem( QString::number( i ), i );
        ui->endBox->addItem( QString::number( i ), i );
    }
    ui->startBox->setCurrentIndex( 0 );
    ui->endBox->setCurrentIndex( 0 );
}

SectionsComboBox::~SectionsComboBox() {
    delete ui;
}

void SectionsComboBox::on_startBox_currentIndexChanged( int index ) {
    QString str = ui->endBox->currentText();
    ui->endBox->clear();
    for ( int i = index + 1; i <= 12; ++i ) {
        ui->endBox->addItem( QString::number( i ), i );
    }
    if ( str.toInt() < index + 1 ) {
        ui->endBox->setCurrentIndex( 0 );
    }
}
