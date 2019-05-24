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
    //设置显示中文
    QTextCodec::setCodecForLocale( QTextCodec::codecForLocale() );

    //菜单点击事件
    connect( ui->actionSettings, &QAction::triggered, this,
             &MainWindow::openSetting );

    /*
     * 以下这些将来都会由类ClassTable完成
     */

    //初始化view
    ui->graphicsView->setGeometry( 0, 0, this->width(), this->height() );
    ui->graphicsView->setAlignment( Qt::AlignLeft | Qt::AlignTop );

    //创建并绑定scene
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene( scene );

    //设置背景图片
    QGraphicsPixmapItem *backgroundImageItemPtr = new QGraphicsPixmapItem();
    QPixmap              backgroundPixmap( "D:/1.jpg" );
    backgroundImageItemPtr->setPixmap( backgroundPixmap.scaled(
        ui->graphicsView->width(), ui->graphicsView->height() ) );
    scene->addItem( backgroundImageItemPtr );

    //绘制边框和底色
    QPen *borderPenPtr = new QPen( QBrush( Qt::white ), 10 );
    borderPenPtr->setJoinStyle( Qt::RoundJoin );
    scene->addRect( 40, 40, 100, 400, *borderPenPtr,
                    QBrush( QColor( 0, 0, 255, 100 ) ) );
    // scene->addRect(10,10,399,399, QPen(Qt::black),QBrush(linearGradient));

    //添加文字
    QGraphicsTextItem *textItemPtr = new QGraphicsTextItem();
    textItemPtr->setPlainText(
        QString::fromLocal8Bit( "数学分析分析分析分析" ) );
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
