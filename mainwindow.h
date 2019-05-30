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
    void setTableWeek( int week, QDate relativeDate );
    void setTableWeek( int week );
    void updateWeekLabel();

protected:
    void resizeEvent( QResizeEvent *event ) override;
    void paintEvent( QPaintEvent *event ) override;
    /*
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    */

    int titleBarHeight;

private slots:
    //打开设置窗口SettingWindow的槽
    void openSetting();

    void on_addButton_clicked();

    void addNewClass();
    void addNewNote();

    void on_leftWeekButton_clicked();
    void on_rightWeekButton_clicked();

private:
    Ui::MainWindow *ui;

    ClassTable *childTablePtr;

    QPoint  mouseLastPos;
    bool    mouseIsPressed = false;
    QCursor mouseLastCursor;
};

#endif   // MAINWINDOW_H
