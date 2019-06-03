#include "mytcpclient.h"

#include <string>

MyTcpClient::MyTcpClient( QWidget *parent = 0 ) {
    tcpClient = new QTcpSocket( this );   //实例化tcpClient
    tcpClient->abort();                   //取消原有连接
    connect( tcpClient, SIGNAL( readyRead() ), this, SLOT( ReadData() ) );
    connect( tcpClient, SIGNAL( error( QAbstractSocket::SocketError ) ), this,
             SLOT( ReadError( QAbstractSocket::SocketError ) ) );
}

void MyTcpClient::connect() {
    tcpClient->connectToHost( 192.168.1.101,
                              81 );               // 服务端
    if ( !tcpClient->waitForConnected( 1000 ) )   // 连接成功则进入if{}
    {
        throw string( "connected error" );
    }
}
void MyTcpClient::disconnect() {
    tcpClient->disconnectFromHost();
    if ( !( tcpClient->state() == QAbstractSocket::UnconnectedState
            || tcpClient->waitForDisconnected(
                1000 ) ) )   //已断开连接则进入if{}
    {
        throw string( "disconnect error" );
    }
}
void MyTcpClient::ReadData() {
    QByteArray buffer = tcpClient->readAll();
    if ( !buffer.isEmpty() ) {
        pass;
    }
}

void MyTcpClient::ReadError( QAbstractSocket::SocketError ) {
    tcpClient->disconnectFromHost();
    QMessageBox msgBox;
    msgBox.setText( tr( "failed to connect server because %1" )
                        .arg( tcpClient->errorString() ) );
    xec();
}

void MyTcpClient::SendData() {
    QString data =   //待填入
        if ( data != "" ) {
        tcpClient->write( data.toLatin1() );   //发送
    }
}
MyTcpClient::~MyTcpClient() {
    disconnect();
    //可能要delete指针
}
