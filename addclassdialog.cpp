#include "addclassdialog.h"
#include "ui_addclassdialog.h"


AddClassDialog::AddClassDialog( QWidget *parent )
    : QDialog( parent ), ui( new Ui::AddClassDialog ) {
    ui->setupUi( this );
}

AddClassDialog::~AddClassDialog() {
    delete ui;
}
