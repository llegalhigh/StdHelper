#include "mytcpsever.h"


MyTcpSever::MyTcpSever() {
    tcpServer = new QTcpServer( this );
    ui->edtIP->setText(
        QNetworkInterface().allAddresses().at( 1 ).toString() );   //��ȡ����IP
    ui->btnConnect->setEnabled( true );
    ui->btnSend->setEnabled( false );

    connect( tcpServer, SIGNAL( newConnection() ), this,
             SLOT( NewConnectionSlot() ) );
    bool ok =
        tcpServer->listen( QHostAddress::Any, ui->edtPort->text().toInt() );
    if ( ok ) {
        ui->btnConnect->setText( "�Ͽ�" );
        ui->btnSend->setEnabled( true );
    }
}
void MyTcpServer::NewConnectionSlot() {
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append( currentClient );
    ui->cbxConnection->addItem(
        tr( "%1:%2" )
            .arg(
                currentClient->peerAddress().toString().split( "::ffff:" )[1] )
            .arg( currentClient->peerPort() ) );
    connect( currentClient, SIGNAL( readyRead() ), this, SLOT( ReadData() ) );
    connect( currentClient, SIGNAL( disconnected() ), this,
             SLOT( disconnectedSlot() ) );
}

void MyTcpServer::disconnectedSlot() {
    for ( int i = 0; i < tcpClient.length(); i++ ) {
        for ( int i = 0; i < tcpClient.length(); i++ )   //�Ͽ���������
        {
            tcpClient[i]->disconnectFromHost();
            bool ok = tcpClient[i]->waitForDisconnected( 1000 );
            if ( !ok ) {
                // �����쳣
            }
            tcpClient.removeAt( i );   //�ӱ���Ŀͻ����б���ȡȥ��
        }
        tcpServer->close();   //���ټ����˿�
        if ( tcpClient[i]->state() == QAbstractSocket::UnconnectedState ) {
            // ɾ���洢��combox�еĿͻ�����Ϣ
            ui->cbxConnection->removeItem( ui->cbxConnection->findText(
                tr( "%1:%2" )
                    .arg( tcpClient[i]->peerAddress().toString().split(
                        "::ffff:" )[1] )
                    .arg( tcpClient[i]->peerPort() ) ) );
            // ɾ���洢��tcpClient�б��еĿͻ�����Ϣ
            tcpClient[i]->destroyed();
            tcpClient.removeAt( i );
        }
    }
}
void MyTcpServer::ReadData() {
    // ����readyRead�źŲ�δ�ṩSocketDecriptor��������Ҫ�������пͻ���
    for ( int i = 0; i < tcpClient.length(); i++ ) {
        QByteArray buffer = tcpClient[i]->readAll();
        if ( buffer.isEmpty() )
            continue;

        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr( "[%1:%2]:" )
                      .arg( tcpClient[i]->peerAddress().toString().split(
                          "::ffff:" )[1] )
                      .arg( tcpClient[i]->peerPort() );

        // ���˴���Ϣ�ĵ�ַ���ϴβ�ͬ��������ʾ�˴���Ϣ�Ŀͻ��˵�ַ
        if ( IP_Port != IP_Port_Pre )
            ui->edtRecv->append( IP_Port );

        ui->edtRecv->append( buffer );

        //����ip_port
        IP_Port_Pre = IP_Port;
    }
}

void MyTcpServer::on_btnSend_clicked() {
    if ( ui->cbxConnection->currentIndex() == 0 ) {
        for ( int i = 0; i < tcpClient.length(); i++ )
            tcpClient[i]->write( data.toLatin1() );   // qt5��ȥ��.toAscii()
    }
    //ָ������
    QString clientIP = ui->cbxConnection->currentText().split( ":" )[0];
    int clientPort   = ui->cbxConnection->currentText().split( ":" )[1].toInt();
    for ( int i = 0; i < tcpClient.length(); i++ ) {
        if ( tcpClient[i]->peerAddress().toString().split( "::ffff:" )[1]
                 == clientIP
             && tcpClient[i]->peerPort() == clientPort ) {
            tcpClient[i]->write( data.toLatin1() );
            return;   // ip:portΨһ�������������
        }
    }
}
