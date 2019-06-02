#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "classtable.h"
#include "link.h"

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    friend class SettingWindow;
    friend class ClassTable;

public:
    explicit MainWindow(QWidget *parent = nullptr );
    ~MainWindow() override;

    void showView();
    int  getMainHeight() const;
    void setTableWeek( int week, QDate relativeDate );
    void setTableWeek( int week );
    void updateWeekLabel();
    void setCourseList(const QJsonArray &); //设置courseList
    void setUser_id(QString);   //设置user_id
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

    void fetch_courseList();    //从服务器上获取课程表并传递给setCourseList2();
    void setCourseList2(QNetworkReply *);   //把课表赋给courseList数据成员
private:
    Ui::MainWindow *ui;

    ClassTable *childTablePtr;

    QPoint  mouseLastPos;
    bool    mouseIsPressed = false;
    QCursor mouseLastCursor;
    QString user_id;    //用户的id
    QJsonArray courseList;    //用户课程json数组
    Link *link;
};

#endif   // MAINWINDOW_H
