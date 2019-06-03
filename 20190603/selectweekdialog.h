#ifndef SELECTWEEKDIALOG_H
#define SELECTWEEKDIALOG_H

#include "weekbuttondelegate.h"

#include <QDialog>

namespace Ui {
class selectWeekDialog;
}

class SelectWeekDialog : public QDialog {
    Q_OBJECT

public:
    explicit SelectWeekDialog( QList< bool >       boolList,
                               WeekButtonDelegate *invoker = nullptr,
                               QWidget *           parent  = nullptr );
    ~SelectWeekDialog();

private slots:
    void on_singleButton_clicked();
    void on_doubleButton_clicked();
    void on_selectAllButton_clicked();
    void on_clearAllButton_clicked();

    void on_buttonBox_accepted();

protected:
    WeekButtonDelegate *delegate;
    int                 termTotalWeek;

private:
    Ui::selectWeekDialog *ui;
};

#endif   // SELECTWEEKDIALOG_H
