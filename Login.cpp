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
    init();
}

Login::~Login()
{
    delete ui;
    delete link;
}

void Login::init()
{
    ui->label_screen->setText(tr("Login Screen"));
    ui->label_confirmpwd->hide();
    ui->lineEdit_confirmpwd->hide();

    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(loginSend()));
    connect(ui->pushButton_register, SIGNAL(clicked()), this, SLOT(changeToRegisterScreen()));
}

void Login::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Login::loginSend()
{
    ui->label_information->setText(QObject::tr("Logining...")); //正在登陆时显示"Logining..."信息

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    link->setUrl("http://111.230.183.100/login.php");   //登陆ip地址(示例)
    link->setParameter("username",username);    //设置参数
    link->addParameter("password",password);    //添加参数
    link->connect(this,SLOT(cancelInformation()));  //绑定槽函数(网络请求完成时触发槽函数)
    link->post();   //发送POST请求
}

void Login::registerSend()
{
    ui->label_information->setText(QObject::tr("Registering...")); //正在登陆时显示"Registering..."信息

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString confirmpwd = ui->lineEdit_confirmpwd->text();

    link->setUrl("http://111.230.183.100/login.php");   //注册ip地址(示例)
    link->setParameter("username",username);    //设置参数
    link->addParameter("password",password);    //添加参数
    link->addParameter("confirmpwd",confirmpwd);
    link->connect(this,SLOT(cancelInformation()));  //绑定槽函数(网络请求完成时触发槽函数)
    link->post();   //发送POST请求

}

void Login::changeToLoginScreen()
{
    ui->pushButton_login->disconnect();
    ui->pushButton_register->disconnect();
    init();
}

void Login::changeToRegisterScreen()
{
    ui->label_screen->setText(tr("Register Screen"));
    ui->label_confirmpwd->show();
    ui->lineEdit_confirmpwd->show();

    ui->pushButton_login->disconnect();
    connect(ui->pushButton_register, SIGNAL(clicked()), this, SLOT(registerSend()));
    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(changeToLoginScreen()));
}

void Login::cancelInformation()
{
    ui->label_information->setText("");
    link->disconnect();
}
