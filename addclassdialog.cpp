#include "addclassdialog.h"

#include "sectionscomboboxdelegate.h"
#include "ui_addclassdialog.h"
#include "weekbuttondelegate.h"
#include "weekcomboboxdelegate.h"

AddClassDialog::AddClassDialog( QWidget *parent )
    : QDialog( parent ), ui( new Ui::AddClassDialog ) {
    ui->setupUi( this );

    WeekComboBoxDelegate *wcbd = new WeekComboBoxDelegate( ui->tableWidget );
    ui->tableWidget->setItemDelegateForColumn( 1, wcbd );

    SectionsComboBoxDelegate *scbd =
        new SectionsComboBoxDelegate( ui->tableWidget );
    ui->tableWidget->setItemDelegateForColumn( 2, scbd );

    WeekButtonDelegate *wbd = new WeekButtonDelegate( ui->tableWidget );
    ui->tableWidget->setItemDelegateForColumn( 3, wbd );
}

AddClassDialog::~AddClassDialog() {
    delete ui;
}

void AddClassDialog::on_addClassButton_clicked() {
    ui->tableWidget->insertRow( 0 );
    // ui->tableWidget->itemAt( 0, 1 )->setData( Qt::UserRole, 1 );
}
