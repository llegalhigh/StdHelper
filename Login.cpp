#include <QStyleOption>
#include <QPainter>
#include "link.h"
#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    link(new Link)
{
    ui->setupUi(this);
    loginInit();
}

Login::~Login()
{
    delete ui;
    delete link;
}

void Login::loginSetTabOrder() const
{
    setTabOrder(ui->lineEdit_username, ui->lineEdit_password);
    setTabOrder(ui->lineEdit_password, ui->pushButton_login);
    setTabOrder(ui->pushButton_login, ui->pushButton_register);
    ui->lineEdit_username->setFocus();
}

void Login::registerSetTabOrder() const
{
    setTabOrder(ui->lineEdit_username, ui->lineEdit_password);
    setTabOrder(ui->lineEdit_password, ui->lineEdit_confirmpwd);
    setTabOrder(ui->lineEdit_confirmpwd, ui->pushButton_login);
    setTabOrder(ui->pushButton_login, ui->pushButton_register);
    ui->lineEdit_username->setFocus();
}

void Login::loginInit() const
{
    ui->label_screen->setText(tr("Login Screen"));
    ui->lineEdit_username->setText(tr(""));
    ui->lineEdit_password->setText(tr(""));
    ui->lineEdit_confirmpwd->setText(tr(""));
    ui->label_confirmpwd->hide();
    ui->lineEdit_confirmpwd->hide();

    ui->pushButton_login->disconnect();
    ui->pushButton_register->disconnect();
    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(loginSend()));
    connect(ui->pushButton_register, SIGNAL(clicked()), this, SLOT(registerInit()));

    loginSetTabOrder();
}

void Login::registerInit() const
{
    ui->label_screen->setText(tr("Register Screen"));
    ui->lineEdit_username->setText(tr(""));
    ui->lineEdit_password->setText(tr(""));
    ui->lineEdit_confirmpwd->setText(tr(""));
    ui->label_confirmpwd->show();
    ui->lineEdit_confirmpwd->show();

    ui->pushButton_login->disconnect();
    ui->pushButton_register->disconnect();
    connect(ui->pushButton_register, SIGNAL(clicked()), this, SLOT(registerSend()));
    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(loginInit()));

    registerSetTabOrder();
}

void Login::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Login::loginSend() const
{
    ui->label_information->setText(QObject::tr("Logining...")); //���ڵ�½ʱ��ʾ"Logining..."��Ϣ

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    link->setUrl("http://111.230.183.100/demo.php");   //��½ip��ַ(ʾ��)
    link->setParameter("username",username);    //���ò���
    link->addParameter("password",password);    //��Ӳ���
    link->connect(this,SLOT(cancelInformation()));  //�󶨲ۺ���(�����������ʱ�����ۺ���)
    link->post();   //����POST����
}

void Login::registerSend() const
{
    ui->label_information->setText(QObject::tr("Registering...")); //���ڵ�½ʱ��ʾ"Registering..."��Ϣ

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString confirmpwd = ui->lineEdit_confirmpwd->text();

    link->setUrl("http://111.230.183.100/login.php");   //ע��ip��ַ(ʾ��)
    link->setParameter("username",username);    //���ò���
    link->addParameter("password",password);    //��Ӳ���
    link->addParameter("confirmpwd",confirmpwd);
    link->connect(this,SLOT(cancelInformation()));  //�󶨲ۺ���(�����������ʱ�����ۺ���)
    link->post();   //����POST����

}

void Login::cancelInformation() const
{
    ui->label_information->setText("");
    link->disconnect();
}
