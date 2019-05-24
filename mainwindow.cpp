#include "mainwindow.h"
#include "settingwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QTextCodec>


MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    //������ʾ����
    QTextCodec::setCodecForLocale( QTextCodec::codecForLocale() );

    //�˵�����¼�
    connect( ui->actionSettings, &QAction::triggered, this,
             &MainWindow::openSetting );

    /*
     * ������Щ������������ClassTable���
     */

    //��ʼ��view
    ui->graphicsView->setGeometry( 0, 0, this->width(), this->height() );
    ui->graphicsView->setAlignment( Qt::AlignLeft | Qt::AlignTop );

    //��������scene
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene( scene );

    //���ñ���ͼƬ
    QGraphicsPixmapItem *backgroundImageItemPtr = new QGraphicsPixmapItem();
    QPixmap              backgroundPixmap( "D:/1.jpg" );
    backgroundImageItemPtr->setPixmap( backgroundPixmap.scaled(
        ui->graphicsView->width(), ui->graphicsView->height() ) );
    scene->addItem( backgroundImageItemPtr );

    //���Ʊ߿�͵�ɫ
    QPen *borderPenPtr = new QPen( QBrush( Qt::white ), 10 );
    borderPenPtr->setJoinStyle( Qt::RoundJoin );
    scene->addRect( 40, 40, 100, 400, *borderPenPtr,
                    QBrush( QColor( 0, 0, 255, 100 ) ) );
    // scene->addRect(10,10,399,399, QPen(Qt::black),QBrush(linearGradient));

    //�������
    QGraphicsTextItem *textItemPtr = new QGraphicsTextItem();
    textItemPtr->setPlainText(
        QString::fromLocal8Bit( "��ѧ����������������" ) );
    textItemPtr->setDefaultTextColor( Qt::white );
    textItemPtr->setPos( 50, 50 );
    textItemPtr->setTextWidth( 90 );
    scene->addItem( textItemPtr );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openSetting() {
    SettingWindow *sw = new SettingWindow;
    sw->show();
}
