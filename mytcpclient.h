#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
using namespace std;

class MyTcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyTcpClient(QWidget *parent);
    ~MyTcpClient();

private:
    MyTcpClient *ui;
    QTcpSocket *tcpClient;

private slots:
    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
    void SendData();
    void connect();
    void disconnect();
};

#endif
