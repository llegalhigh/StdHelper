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
    friend class ClassTable;

public:
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow() override;

    void showView();
    int  getMainHeight() const;

protected:
    void resizeEvent( QResizeEvent *event ) override;

private slots:
    //打开设置窗口SettingWindow的槽
    void openSetting();

private:
    Ui::MainWindow *ui;

    ClassTable *childTablePtr;
};

#endif   // MAINWINDOW_H
