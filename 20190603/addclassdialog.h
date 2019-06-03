#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class AddClassDialog;
}

class AddClassDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddClassDialog( QWidget *parent = nullptr );
    ~AddClassDialog();

protected:
    void        updateColorReview();
    void        insertDefaultRow();
    MainWindow *mainWindowPtr;

private slots:
    void on_addClassButton_clicked();
    void on_rSlider_valueChanged( int value );
    void on_gSlider_valueChanged( int value );
    void on_bSlider_valueChanged( int value );
    void on_opacitySlider_valueChanged( int value );
    void on_AddClassDialog_accepted();
    void on_buttonBox_accepted();

private:
    Ui::AddClassDialog *ui;
};

#endif   // ADDCLASSDIALOG_H
