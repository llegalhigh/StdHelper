#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MyTcpServer;
}

class MyTcpServer : public QMainWindow {
    Q_OBJECT

public:
    explicit MyTcpServer( QWidget *parent = 0 );
    ~MyTcpServer();

private:
    Ui::MyTcpServer *     ui;
    QTcpServer *          tcpServer;
    QList< QTcpSocket * > tcpClient;
    QTcpSocket *          currentClient;

private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadData();

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
};

#endif   // MYTCPSERVER_H
