#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "link.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void init();

protected:
    void paintEvent(QPaintEvent *); //重构QWidget函数, 使其能够显示背景图片

private slots:
    void loginSend(); //login按键clicked事件,发送登陆请求
    void registerSend();    //register按键clicked事件,发送注册请求
    void changeToLoginScreen(); //切换到登陆页面
    void changeToRegisterScreen();  //切换到注册页面
    void cancelInformation();   //当得到网络回应时取消显示的"Logining..."或"Registering..."信息

private:
    Ui::Login *ui;
    Link *link;
};

#endif // LOGIN_H
