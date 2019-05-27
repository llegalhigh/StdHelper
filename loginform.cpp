#include "loginform.h"
#include "ui_loginform.h"
#include <QtGui>

loginForm::loginForm(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::loginForm) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    /*
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setBrush(backgroundRole(), QPixmap("/Images/loginBackground.jpg"));
    setPalette(pal);
    */
}

loginForm::~loginForm() {
    delete ui;
}

void loginForm::on_pushButton_clicked() {
    mainWindow = new MainWindow;
    mainWindow->show();
    this->close();
    return;
}
