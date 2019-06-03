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
    void loginSetTabOrder() const;	//�Ե�½ҳ������Tab��˳��, ����ʼ������
    void registerSetTabOrder() const;	//��ע��ҳ������Tab��˳��, ����ʼ������

protected:
    void paintEvent(QPaintEvent *); //�ع�QWidget����, ʹ���ܹ���ʾ����ͼƬ

private slots:
    void loginSend() const; //login����clicked�¼�,���͵�½����
    void registerSend() const;    //register����clicked�¼�,����ע������
    void cancelInformation() const;   //���õ������Ӧʱȡ����ʾ��"Logining..."��"Registering..."��Ϣ
    void showInformationL(QNetworkReply *);   //��ʾ��½״̬��Ϣ
    void showInformationR(QNetworkReply *) const;   //��ʾע��״̬��Ϣ
    void loginInit() const;   //��ʼ���ɵ�½ҳ��
    void registerInit() const;    //��ʼ����ע��ҳ��

private:
    Ui::Login *ui;
    Link *link;
    MainWindow *mainWindow;
};

#endif // LOGIN_H
