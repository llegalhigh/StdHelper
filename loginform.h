#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "mainwindow.h"

#include <QDialog>


namespace Ui {
class loginForm;
}

class loginForm : public QDialog {
    Q_OBJECT

public:
    explicit loginForm( QWidget *parent = nullptr );
    ~loginForm();
    MainWindow *mainWindow;

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginForm *ui;
};

#endif   // LOGINFORM_H
