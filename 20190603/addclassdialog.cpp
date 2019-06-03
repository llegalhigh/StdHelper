#include "addclassdialog.h"

#include "classtable.h"
#include "classtableitem.h"
#include "sectionscomboboxdelegate.h"
#include "ui_addclassdialog.h"
#include "weekbuttondelegate.h"
#include "weekcomboboxdelegate.h"

#include <QMessageBox>

AddClassDialog::AddClassDialog( QWidget *parent )
    : QDialog( parent ),
      mainWindowPtr( qobject_cast< MainWindow * >( parent ) ),
      ui( new Ui::AddClassDialog ) {
    ui->setupUi( this );

    WeekComboBoxDelegate *wcbd = new WeekComboBoxDelegate( ui->tableWidget );
    ui->tableWidget->setItemDelegateForColumn( 1, wcbd );

    SectionsComboBoxDelegate *scbd =
        new SectionsComboBoxDelegate( ui->tableWidget );
    ui->tableWidget->setItemDelegateForColumn( 2, scbd );

    WeekButtonDelegate *wbd =
        new WeekButtonDelegate( ui->tableWidget, mainWindowPtr );
    ui->tableWidget->setItemDelegateForColumn( 3, wbd );

    insertDefaultRow();
    ui->tableWidget->resizeColumnsToContents();
}

AddClassDialog::~AddClassDialog() {
    delete ui;
}

/** @brief 更新预览颜色 */
void AddClassDialog::updateColorReview() {
    ui->previewBlock->setStyleSheet(
        QString( "background-color: rgba(%1, %2, %3, %4);" )
            .arg( ui->rSlider->value() )
            .arg( ui->gSlider->value() )
            .arg( ui->bSlider->value() )
            .arg( ui->opacitySlider->value() ) );
}

void AddClassDialog::insertDefaultRow() {
    ui->tableWidget->insertRow( 0 );
    ui->tableWidget->setItem( 0, 0, new QTableWidgetItem( "A1-101" ) );
    ui->tableWidget->setItem( 0, 1, new QTableWidgetItem( "Monday" ) );
    ui->tableWidget->setItem( 0, 2, new QTableWidgetItem( "5~7" ) );
    ui->tableWidget->setItem( 0, 3,
                              new QTableWidgetItem( "1,2,3,4,5,6,7,8,9" ) );
}

void AddClassDialog::on_addClassButton_clicked() {
    insertDefaultRow();
}

void AddClassDialog::on_rSlider_valueChanged( int ) {
    updateColorReview();
}

void AddClassDialog::on_gSlider_valueChanged( int ) {
    updateColorReview();
}

void AddClassDialog::on_bSlider_valueChanged( int ) {
    updateColorReview();
}

void AddClassDialog::on_opacitySlider_valueChanged( int ) {
    updateColorReview();
}

void AddClassDialog::on_AddClassDialog_accepted() {}

void AddClassDialog::on_buttonBox_accepted() {
    QString className     = ui->classNameBox->currentText();
    QString classAbbrName = ui->classShortNameLineEdit->text();
    QString teacherName   = ui->teacherNameLineEdit->text();
    if ( className.isEmpty() || classAbbrName.isEmpty()
         || teacherName.isEmpty() ) {
        QMessageBox emptyTextMsgBox( this );
        emptyTextMsgBox.setWindowTitle( "Failed to add new class" );
        emptyTextMsgBox.setText( "Name information is incomplete!" );
        emptyTextMsgBox.setIcon( QMessageBox::Information );
        emptyTextMsgBox.setStandardButtons( QMessageBox::Ok );
        emptyTextMsgBox.exec();
    } else if ( className.length() <= classAbbrName.length() ) {
        QMessageBox tooLongMsgBox( this );
        tooLongMsgBox.setWindowTitle( "Failed to add new class" );
        tooLongMsgBox.setText( "Short name should be shorter than full name!" );
        tooLongMsgBox.setIcon( QMessageBox::Information );
        tooLongMsgBox.setStandardButtons( QMessageBox::Ok );
        tooLongMsgBox.exec();
    } else {
        QTableWidget *tableWidgetPtr = ui->tableWidget;
        int           rowCount       = tableWidgetPtr->rowCount();
        if ( rowCount < 1 ) {
            QMessageBox emptyRowMsgBox( this );
            emptyRowMsgBox.setWindowTitle( "Failed to add new class" );
            emptyRowMsgBox.setText( "No subclass is added!" );
            emptyRowMsgBox.setIcon( QMessageBox::Information );
            emptyRowMsgBox.setStandardButtons( QMessageBox::Ok );
            emptyRowMsgBox.exec();
        } else {
            ClassTable *    tablePtr  = mainWindowPtr->childTablePtr;
            ClassTableItem *classItem = new ClassTableItem(
                className, classAbbrName, teacherName, tablePtr );
            for ( int row = 0; row < rowCount; ++row ) {   //每一row是一节课
                //上课地点
                QString location = tableWidgetPtr->item( row, 0 )->text();
                //星期几上
                int classDayOfWeek =
                    tableWidgetPtr->item( row, 1 )->text().toInt();
                //将第几节到第几节转化为具体时间
                QString sectionString = tableWidgetPtr->item( row, 2 )->text();
                QStringList sectionStringList = sectionString.split( "~" );
                QPair< int, int > sections{ sectionStringList[0].toInt(),
                                            sectionStringList[1].toInt() };
                //第几周
                QList< bool > classIsInWeek;
                for ( int i = 0;
                      i < mainWindowPtr->childTablePtr->termTotalWeek; ++i ) {
                    classIsInWeek.append( false );
                }
                const QStringList boolStrList =
                    tableWidgetPtr->item( row, 3 )->text().split( "," );
                foreach ( QString boolStr, boolStrList ) {
                    classIsInWeek[boolStr.toInt() - 1] = true;
                }

                //创建Subclass
                Subclass *subclass = new Subclass(
                    ClassTable::dayOfWeek( classDayOfWeek ),
                    tablePtr->sectionTime[sections.first].first,
                    tablePtr->sectionTime[sections.second].second, location );
                subclass->isInWeek = classIsInWeek;
                //加入ClassTableItem
                classItem->addSubclass( *subclass );
            }
            mainWindowPtr->childTablePtr->addItem( classItem );
            this->accept();
        }
    }
}
