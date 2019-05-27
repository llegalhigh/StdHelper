#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QDebug>

//数据存储
#include <QVariant>

//通知
#include <QMessageBox>


/*****************************************************************************
 * 设置文件: setting.dat
 *
 * 设置项:
 *  index    name & description & type
 *  0        termStartDate, 本学期从什么时候开始(QDate)
 *  1        termTotalWeek, 本学期有多少周(quint8)
 *
 * 文件内容: 4字节魔术数字+4字节版本号+100字节设置0+100字节设置1+...
 *
 * 二进制文件读写参考：
 * https://www.devbean.net/2013/01/qt-study-road-2-binary-file-io/
 *****************************************************************************/

static constexpr quint32 MAGIC_NUMBER    = 0xBAD00CAB;   //魔术数字
static constexpr qint32  CURRENT_VERSION = 100;          //版本
static constexpr qint64  OFFSET   = 8;   //魔术数字和版本号占8字节
static constexpr qint64 ITEM_SIZE = sizeof( QVariant );   //设置占的字节数
const QString SETTING_FILE_PATH = "D:/setting.dat";   //设置文件存储的路径

/** 窗口构造函数 */
SettingWindow::SettingWindow( MainWindow *parentMain, QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::SettingWindow ),
      mainWindowPtr( parentMain ) {
    qDebug() << "Setting window opened";
    ui->setupUi( this );

    ui->termStartDateEdit->setMinimumDate(
        QDate::currentDate().addYears( -2 ) );
    ui->termStartDateEdit->setMaximumDate( QDate::currentDate().addYears( 2 ) );

    //设置文件:setting.dat
    QFile settingFile( SETTING_FILE_PATH );

    if ( !settingFile.open(
             QIODevice::ReadOnly ) ) {       //如果setting.dat读取失败
        rewriteSettingFile( settingFile );   //重写文件(询问?)
        updateWindow();                      //更新窗口
    } else {
        QDataStream readStream( &settingFile );
        //检查魔术数字
        quint32 readMagicNumber;
        readStream >> readMagicNumber;
        qDebug() << "\treadMagicNumber: " << readMagicNumber;
        if ( readMagicNumber != MAGIC_NUMBER ) {
            rewriteSettingFile( settingFile );
        } else {
            //检查版本
            qint32 readVersion;
            readStream >> readVersion;
            qDebug() << "\treadVersion: " << readVersion;
            if ( readVersion < CURRENT_VERSION ) {
                rewriteSettingFile( settingFile );

                QMessageBox oldFileMsgBox;
                oldFileMsgBox.setText(
                    tr( "Existed setting file is of old version." ) );
                oldFileMsgBox.setInformativeText(
                    tr( "It has been replaced with a default new one." ) );
                oldFileMsgBox.setStandardButtons( QMessageBox::Ok );

                oldFileMsgBox.exec();
            }
            readStream.setVersion( QDataStream::Qt_5_12 );

            updateWindow( readStream );
        }
    }

    settingFile.close();
}

/** 窗口析构函数 */
SettingWindow::~SettingWindow() {
    delete ui;
}

/**
 * @brief   槽，保存界面上所有设置项
 * @warning
 * @todo
 */
void SettingWindow::saveAll() {
    QFile settingFile( SETTING_FILE_PATH );
    settingFile.open( QIODevice::ReadWrite );

    QDataStream writeStream( &settingFile );

    writeSettingItem( 0, QVariant( this->ui->termStartDateEdit->date() ),
                      writeStream );
    writeSettingItem( 1, QVariant( this->ui->totalWeekBox->value() ),
                      writeStream );
}

/**
 * @brief   完全重写dat，恢复默认值
 * @warning
 * @todo    上传数据库版本
 */
void SettingWindow::rewriteSettingFile( QFile &f ) {
    qDebug() << "Start rewriting";
    QIODevice::OpenMode originalMode = f.openMode();
    f.close();
    f.open( QIODevice::WriteOnly );
    QDataStream rewriteStream( &f );
    rewriteStream.device()->seek( 0 );
    rewriteStream << MAGIC_NUMBER;      //魔术数字
    rewriteStream << CURRENT_VERSION;   //版本
    // qDebug() << rewriteStream.device()->pos();
    writeSettingItem( 0, QVariant( QDate( 2019, 2, 25 ) ), rewriteStream );
    writeSettingItem( 1, QVariant( (quint8)20 ), rewriteStream );
    f.close();
    f.open( originalMode );
    qDebug() << "End rewriting";
}

/**
 * @brief   通过stream将第index项设置写入dat
 * @warning stream需要write权限
 * @todo    1. 要想一个方法，既不限制字节，又好定位；
 *          2. 要加入上传数据库
 */
void SettingWindow::writeSettingItem( const qint64 index, QVariant content,
                                      QDataStream &stream ) {
    stream.device()->seek( index * ITEM_SIZE + OFFSET );
    stream << content;
    //上面这样能正确保存，但不能限制字节
    // stream.device()->write(content.toByteArray().left(ITEM_SIZE));
    //上面这样能限制字节，但不能正确保存
}

/**
 * @brief   通过stream从dat中读取第index项设置
 * @warning stream需要read权限
 * @todo    需要数据库读取版本
 */
QVariant SettingWindow::readSettingItem( const qint64 index,
                                         QDataStream &stream ) {
    stream.device()->seek( index * ITEM_SIZE + OFFSET );
    // QByteArray itemData = stream.device()->read(ITEM_SIZE);
    // QDataStream converter(&itemData, QIODevice::ReadWrite);
    // QVariant readItem = QVariant(converter);
    //上面这样建立在限制字节的基础上
    return QVariant( stream );
}

/**
 * @brief   通过stream读取第index项设置，并通过mainPtr将其传递到MainWindow中
 * @note    static
 * @return  第index项设置对应的QVariant
 * @warning 前提是已经确保setting.dat合法，且stream有read权限
 */
QVariant SettingWindow::passOne( const qint64 index, QDataStream &stream,
                                 MainWindow *mainPtr ) {
    switch ( index ) {
        case 0: {   // switch-case只有在大括号内能创建对象
            QDate termStartDate = readSettingItem( 0, stream ).value< QDate >();
            mainPtr->childTablePtr->termStartDate = termStartDate;
            return termStartDate;
        }
        case 1: {
            quint8 termTotalWeek =
                readSettingItem( 1, stream ).value< quint8 >();
            mainPtr->childTablePtr->termTotalWeek = termTotalWeek;
            return termTotalWeek;
        }
        default: return QVariant();
    }
}

/**
 * @brief   通过stream读取第index项设置以更新SettingWindow，并传递到MainWindow中
 * @warning 前提是已经确保setting.dat合法，且stream有read权限
 */
void SettingWindow::updateOne( const qint64 index, QDataStream &stream ) {
    QVariant getSettingItem = passOne( index, stream, mainWindowPtr );
    switch ( index ) {
        case 0: {
            this->ui->termStartDateEdit->setDate( getSettingItem.toDate() );
            break;
        }
        case 1: {
            this->ui->totalWeekBox->setValue(
                getSettingItem.value< quint8 >() );
            break;
        }
    }
}

/**
 * @brief   通过stream读取dat以更新设置窗口，并传递至MainWindow
 * @warning 前提是已经确保setting.dat合法，且stream有read权限
 * @todo    无？
 */
void SettingWindow::updateWindow( QDataStream &stream ) {
    for ( qint64 index = 0; index <= MAX_SETTING_INDEX; ++index ) {
        updateOne( index, stream );
    }
}
/** @overload 用内部的stream */
void SettingWindow::updateWindow() {
    QFile settingFile( SETTING_FILE_PATH );
    settingFile.open( QIODevice::ReadOnly | QIODevice::ExistingOnly );
    QDataStream readStream( &settingFile );
    updateWindow( readStream );
}

void SettingWindow::passAll( MainWindow *mainPtr ) {
    QFile settingFile( SETTING_FILE_PATH );

    if ( !settingFile.open(
             QIODevice::ReadOnly ) ) {       //如果setting.dat读取失败
        rewriteSettingFile( settingFile );   //重写文件(询问?)
    }

    QDataStream readStream( &settingFile );
    for ( qint64 index = 0; index <= MAX_SETTING_INDEX; ++index ) {
        passOne( index, readStream, mainPtr );
    }
}

void SettingWindow::on_applyButton_clicked() {
    saveAll();
}

void SettingWindow::on_cancelButton_clicked() {
    this->close();
}

void SettingWindow::on_okButton_clicked() {
    saveAll();
    this->close();
}
