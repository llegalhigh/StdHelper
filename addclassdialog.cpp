#include "addclassdialog.h"

#include "sectionscomboboxdelegate.h"
#include "ui_addclassdialog.h"
#include "weekbuttondelegate.h"
#include "weekcomboboxdelegate.h"
#include <QtDebug>

AddClassDialog::AddClassDialog(QWidget *parent )
    : QDialog( parent ), ui( new Ui::AddClassDialog ), link(new Link()){
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
    delete link;
}

void AddClassDialog::setUser_id(QString id)
{
    user_id = id;
}

void AddClassDialog::on_addClassButton_clicked() {
    ui->tableWidget->insertRow( 0 );
    // ui->tableWidget->itemAt( 0, 1 )->setData( Qt::UserRole, 1 );


    qDebug()<<this->user_id;
}

void AddClassDialog::addCourse(QString user_id, QString name, QString abbr, QString teacher,
                               QString location, QString week, QString day, QString start, QString end)
{
    link->setUrl("http://111.230.183.100/QT/addCourse.php");   //ip��ַ
    link->setParameter("user_id",user_id);    //���ò���
    link->addParameter("name",name);    //��Ӳ���
    link->addParameter("abbr",abbr);
    link->addParameter("teacher",teacher);    //���ò���
    link->addParameter("location",location);    //��Ӳ���
    link->addParameter("week",week);
    link->addParameter("day",day);    //���ò���
    link->addParameter("start",start);    //��Ӳ���
    link->addParameter("end",end);
    //link->connect(this,SLOT(information(QNetworkReply *))); //�󶨲ۺ���(�����������ʱ�����ۺ���),��ʾ������Ϣ
    link->post();
}
