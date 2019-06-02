#ifndef ADDCLASSDIALOG_H
#define ADDCLASSDIALOG_H

#include <QDialog>
#include <link.h>

namespace Ui {
class AddClassDialog;
}

class AddClassDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddClassDialog(QWidget *parent = nullptr );
    ~AddClassDialog();

    void setUser_id(QString);

private slots:
    void on_addClassButton_clicked();
    void addCourse(QString user_id, QString name, QString abbr, QString teacher,
                                   QString location, QString week, QString day, QString start, QString end);
private:
    Ui::AddClassDialog *ui;
    Link *link;
    QString user_id;    //”√ªßid
};

#endif   // ADDCLASSDIALOG_H
