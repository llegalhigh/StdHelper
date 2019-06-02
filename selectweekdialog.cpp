#include "selectweekdialog.h"

#include "ui_selectweekdialog.h"

#include <QCheckBox>
#include <QTableWidget>

SelectWeekDialog::SelectWeekDialog( QList< bool > &     boolList,
                                    WeekButtonDelegate *invoker,
                                    QWidget *           parent )
    : QDialog( parent ), delegate( invoker ), ui( new Ui::selectWeekDialog ) {
    ui->setupUi( this );

    for ( int i = 1; i <= 20; ++i ) {
        QCheckBox *box = new QCheckBox;
        box->setText( QString::number( i ) );
        box->setCheckState( boolList[i - 1] ? Qt::Checked : Qt::Unchecked );
        ui->gridLayout->addWidget( box, ( i - 1 ) / 5, ( i - 1 ) % 5 );
    }
}

SelectWeekDialog::~SelectWeekDialog() {
    delete ui;
}

void SelectWeekDialog::on_singleButton_clicked() {
    for ( int i = 0; i < 20; i += 2 ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Checked );
    }
    for ( int i = 1; i < 20; i += 2 ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Unchecked );
    }
}

void SelectWeekDialog::on_doubleButton_clicked() {
    for ( int i = 0; i < 20; i += 2 ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Unchecked );
    }
    for ( int i = 1; i < 20; i += 2 ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Checked );
    }
}
void SelectWeekDialog::on_selectAllButton_clicked() {
    for ( int i = 0; i < 20; ++i ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Checked );
    }
}

void SelectWeekDialog::on_clearAllButton_clicked() {
    for ( int i = 0; i < 20; ++i ) {
        qobject_cast< QCheckBox * >(
            ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
            ->setCheckState( Qt::Unchecked );
    }
}

void SelectWeekDialog::on_buttonBox_accepted() {
    QList< bool > isIn;
    for ( int i = 0; i < 20; ++i ) {
        isIn.append(
            qobject_cast< QCheckBox * >(
                ui->gridLayout->itemAtPosition( i / 5, i % 5 )->widget() )
                ->isChecked() );
    }
    delegate->isInWeek = isIn;   //´«µÝ¸ødelegate
}
