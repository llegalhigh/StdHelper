#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "classtable.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    friend class SettingWindow;

public:
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    void showView();

private slots:
    //打开设置窗口SettingWindow的槽
    void openSetting();

private:
    Ui::MainWindow *ui;

    ClassTable *childTablePtr;
};

#endif   // MAINWINDOW_H
