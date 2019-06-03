#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QHostAddress>
#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>

using namespace std;

class MyTcpClient : public QMainWindow {
    Q_OBJECT

public:
    explicit MyTcpClient( QWidget *parent );
    ~MyTcpClient();

private:
    MyTcpClient *ui;
    QTcpSocket * tcpClient;

private slots:
    //¿Í»§¶Ë²Ûº¯Êý
    void ReadData();
    void ReadError( QAbstractSocket::SocketError );
    void SendData();
    void connect();
    void disconnect();
};

#endif
