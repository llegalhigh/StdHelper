#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showView();

private slots:
    //打开设置窗口SettingWindow的槽
    void openSetting();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
