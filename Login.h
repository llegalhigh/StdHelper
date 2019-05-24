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
    void paintEvent(QPaintEvent *); //�ع�QWidget����, ʹ���ܹ���ʾ����ͼƬ

private slots:
    void loginSend(); //login����clicked�¼�,���͵�½����
    void registerSend();    //register����clicked�¼�,����ע������
    void changeToLoginScreen(); //�л�����½ҳ��
    void changeToRegisterScreen();  //�л���ע��ҳ��
    void cancelInformation();   //���õ������Ӧʱȡ����ʾ��"Logining..."��"Registering..."��Ϣ

private:
    Ui::Login *ui;
    Link *link;
};

#endif // LOGIN_H
