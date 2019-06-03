#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "link.h"
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void loginSetTabOrder() const;	//对登陆页面设置Tab的顺序, 并初始化焦点
    void registerSetTabOrder() const;	//对注册页面设置Tab的顺序, 并初始化焦点

protected:
    void paintEvent(QPaintEvent *); //重构QWidget函数, 使其能够显示背景图片

private slots:
    void loginSend() const; //login按键clicked事件,发送登陆请求
    void registerSend() const;    //register按键clicked事件,发送注册请求
    void cancelInformation() const;   //当得到网络回应时取消显示的"Logining..."或"Registering..."信息
    void showInformationL(QNetworkReply *);   //显示登陆状态信息
    void showInformationR(QNetworkReply *) const;   //显示注册状态信息
    void loginInit() const;   //初始化成登陆页面
    void registerInit() const;    //初始化成注册页面

private:
    Ui::Login *ui;
    Link *link;
    MainWindow *mainWindow;
};

#endif // LOGIN_H
