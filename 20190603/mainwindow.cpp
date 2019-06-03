#include "mainwindow.h"

#include "addclassdialog.h"
#include "settingwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QTextCodec>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    qDebug( ": MainWindow constructor {" );
    ui->setupUi( this );

    ui->menuBar->hide();   //���ز˵���
    this->setWindowFlags( Qt::FramelessWindowHint );

    QMenu *addMenu = new QMenu;
    addMenu->addAction( QIcon( ":/icon/add.ico" ), tr( "Class" ), this,
                        &MainWindow::addNewClass );
    addMenu->addAction( QIcon( ":/icon/add.ico" ), tr( "Note" ), this,
                        &MainWindow::addNewNote );
    ui->addButton->setMenu( addMenu );

    //������ʽ
    QFile qssFile( ":/black.qss" );
    qssFile.open( QFile::ReadOnly );
    QString styleSheet = tr( qssFile.readAll() );
    this->setStyleSheet( styleSheet );
    qssFile.close();

    childTablePtr = new ClassTable( this, ui->graphicsView );
    //������ʾ����
    QTextCodec::setCodecForLocale( QTextCodec::codecForLocale() );

    //�˵�����¼�
    connect( ui->actionSettings, &QAction::triggered, this,
             &MainWindow::openSetting );

    //��dat��ȡ����������
    SettingWindow::passAll( this );

    childTablePtr->addItem( new TableItem(
        "Multi-week", QDateTime( QDate( 2019, 5, 24 ), QTime( 15, 35 ) ),
        QDateTime( QDate( 2019, 5, 27 ), QTime( 6, 0 ) ), childTablePtr ) );
    childTablePtr->addItem( new TableItem(
        "Physics", QDateTime( QDate( 2019, 5, 27 ), QTime( 8, 50 ) ),
        QDateTime( QDate( 2019, 5, 27 ), QTime( 10, 25 ) ), childTablePtr ) );
    childTablePtr->addItem( new TableItem(
        "Mathematics", QDateTime( QDate( 2019, 5, 27 ), QTime( 10, 40 ) ),
        QDateTime( QDate( 2019, 5, 27 ), QTime( 12, 15 ) ), childTablePtr ) );

    setTableWeek( childTablePtr->whichWeek() );

    qDebug( ": } MainWindow constructor " );
}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::getMainHeight() const {
    return this->height() - ui->menuBar->height();
}

/**
 * @brief
 * @warning ʹ��֮ǰȷ���Ѿ�passAll
 * @todo
 */
void MainWindow::setTableWeek( int week, QDate relativeDate ) {
    childTablePtr->setWeek( week, relativeDate );
    updateWeekLabel();
    childTablePtr->draw();
}

void MainWindow::setTableWeek( int week ) {
    setTableWeek( week, childTablePtr->termStartDate );
}
/** setTableWeek���ؽ��� */

/**
 * @brief   �����������йصĴ�������
 * @warning ʹ��֮ǰȷ���Ѿ�passAll
 * @todo
 */
void MainWindow::updateWeekLabel() {
    int week          = childTablePtr->weekOnTable;
    int nowWhichWeek  = childTablePtr->whichWeek();
    int termTotalWeek = childTablePtr->termTotalWeek;

    ui->weekLabel->setText( tr( "Week %1" ).arg( week ) );
    ui->weekDateLabel->setText(
        tr( "%1 ~ %2" )
            .arg( childTablePtr->start.toString( "yyyy.M.d" ),
                  childTablePtr->end.toString( "yyyy.M.d" ) ) );
    if ( nowWhichWeek < 1 ) {   //�����ǰѧ��δ��ʼ
        if ( week < 1 ) {
            ui->weekDetailLabel->setText(
                tr( "Week %1 to school!" ).arg( 1 - week ) );
        } else if ( week <= childTablePtr->termTotalWeek ) {
            ui->weekDetailLabel->setText( "Semester not started" );
        } else {
            ui->weekDetailLabel->setText(
                tr( "Week %1 after semester will end" )
                    .arg( week - termTotalWeek ) );
        }
    } else if ( nowWhichWeek <= termTotalWeek ) {   //����Ѿ���ѧ
        if ( week < 1 ) {
            ui->weekDetailLabel->setText(
                tr( "Week %1 before semester started" ).arg( 1 - week ) );
        } else if ( week <= childTablePtr->termTotalWeek ) {
            if ( week < nowWhichWeek )
                ui->weekDetailLabel->setText( tr( "Finished" ) );
            else if ( week == nowWhichWeek )
                ui->weekDetailLabel->setText( tr( "Current week" ) );
            else
                ui->weekDetailLabel->setText( tr( "Future" ) );
        } else {
            ui->weekDetailLabel->setText(
                tr( "Week %1 after semester will end" )
                    .arg( week - termTotalWeek ) );
        }
    } else {   //���ѧ���ѹ�
        if ( week < 1 ) {
            ui->weekDetailLabel->setText(
                tr( "Week %1 before semester started" ).arg( 1 - week ) );
        } else if ( week <= childTablePtr->termTotalWeek ) {
            ui->weekDetailLabel->setText( tr( "Finished" ) );
        } else {
            ui->weekDetailLabel->setText( tr( "Week %1 after semester ended" )
                                              .arg( week - termTotalWeek ) );
        }
    }
}

void MainWindow::resizeEvent( QResizeEvent *event ) {
    childTablePtr->resize();
}

/**
 * @brief   ���ش����paint�¼�
 * @warning ɾ������¼��ᵼ�³�ʼ��ʾ����
 */
void MainWindow::paintEvent( QPaintEvent *event ) {
    QMainWindow::paintEvent( event );
    childTablePtr->resize();
}

void MainWindow::mousePressEvent( QMouseEvent *event ) {
    this->setFocus();
    mouseIsPressed = true;
    if ( Qt::ArrowCursor == this->cursor() && Qt::LeftButton == event->button()
         && 0 == ( Qt::WindowMaximized & this->windowState() ) ) {
        mouseLastPos    = event->pos();
        mouseLastCursor = this->cursor();
        event->ignore();
    }
}

void MainWindow::mouseMoveEvent( QMouseEvent *event ) {
    if ( this->isMaximized() )
        return;
    if ( mouseIsPressed && 0 != ( Qt::LeftButton & event->buttons() ) ) {
        //�ı���
        this->setCursor( Qt::ClosedHandCursor );
        //�ƶ�����
        QPoint newPos  = event->globalPos() - mouseLastPos;
        titleBarHeight = frameGeometry().height() - geometry().height();
        newPos.ry() -= titleBarHeight;
        this->move( newPos );
    }
}

void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
    //�ָ����
    this->setCursor( mouseLastCursor );
    event->ignore();
    mouseIsPressed = false;
}

void MainWindow::openSetting() {
    SettingWindow *sw = new SettingWindow( this, this );
    sw->show();
}

void MainWindow::on_addButton_clicked() {
    ui->addButton->showMenu();
}

void MainWindow::addNewClass() {
    AddClassDialog *acd = new AddClassDialog( this );
    acd->show();
}

void MainWindow::addNewNote() {}

void MainWindow::on_leftWeekButton_clicked() {
    qDebug( "** LeftWeekButton clicked {" );
    setTableWeek( childTablePtr->weekOnTable - 1 );
    qDebug( "** } LeftWeekButton clicked" );
}

void MainWindow::on_rightWeekButton_clicked() {
    qDebug( "** RightWeekButton clicked {" );
    setTableWeek( childTablePtr->weekOnTable + 1 );
    qDebug( "** } RightWeekButton clicked" );
}
