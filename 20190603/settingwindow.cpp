#include "settingwindow.h"

#include "timeeditdelegate.h"
#include "ui_settingwindow.h"

#include <QDebug>
//���ݴ洢
#include <QVariant>
//֪ͨ
#include <QMessageBox>

/*****************************************************************************
 * �����ļ�·��: SETTING_FILE_PATH
 *
 * ������:
 *  index   |name & description & type
 * ---------+---------------------------------------
 *  0        termStartDate, ��ѧ�ڴ�ʲôʱ��ʼ(QDate)
 *  1        termTotalWeek, ��ѧ���ж�����(quint8)
 *  2~23
 *��1�ڿ�ʼʱ��(2)����2�ڿ�ʼʱ�䣬��������11�ڿ�ʼʱ��(12)����1�ڽ���ʱ��(13)������(QTime)
 *
 * dat�ļ�����:
 *  4�ֽ�ħ������(quint32) -> 4�ֽڰ汾��(qint32) -> ITEM_SIZE�ֽ�����0
 *  -> ITEM_SIZE�ֽ�����1 -> ...
 *
 * �������ļ���д�ο���
 * https://www.devbean.net/2013/01/qt-study-road-2-binary-file-io/
 *****************************************************************************/

static constexpr quint32 MAGIC_NUMBER    = 0xBAD00CAB;   //ħ������
static constexpr qint32  CURRENT_VERSION = 100;          //�汾
static constexpr qint64  OFFSET   = 8;   //ħ�����ֺͰ汾��ռ8�ֽ�
static constexpr qint64 ITEM_SIZE = sizeof( QVariant );   //����ռ���ֽ���
const QString SETTING_FILE_PATH = "setting.dat";   //�����ļ��洢��·��

/** ���ڹ��캯�� */
SettingWindow::SettingWindow( MainWindow *parentMain, QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::SettingWindow ),
      mainWindowPtr( parentMain ) {
    qDebug() << "Setting window opened";
    //��ʼ������
    ui->setupUi( this );
    ui->termStartDateEdit->setMinimumDate(
        QDate::currentDate().addYears( -2 ) );
    ui->termStartDateEdit->setMaximumDate(
        QDate::currentDate().addYears( +2 ) );
    ui->tableWidget->setItemDelegate( new TimeEditDelegate( ui->tableWidget ) );

    //�����ļ�:setting.dat
    QFile settingFile( SETTING_FILE_PATH );

    if ( !settingFile.open(
             QIODevice::ReadOnly ) ) {       //���setting.dat��ȡʧ��
        rewriteSettingFile( settingFile );   //��д�ļ�
        updateWindow();                      //���´���
    } else {
        QDataStream readStream( &settingFile );
        //���ħ������
        quint32 readMagicNumber;
        readStream >> readMagicNumber;
        qDebug() << "\treadMagicNumber: " << readMagicNumber;
        if ( readMagicNumber != MAGIC_NUMBER ) {
            rewriteSettingFile( settingFile );
        } else {
            //���汾
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

/** ������������ */
SettingWindow::~SettingWindow() {
    delete ui;
}

/**
 * @brief   �ۣ��������������������
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
    for ( int row = 0; row < 11; ++row ) {
        writeSettingItem( row + 2,
                          QVariant( this->ui->tableWidget->item( row, 0 )
                                        ->data( Qt::UserRole )
                                        .toTime() ),
                          writeStream );   //��ʼʱ��
        writeSettingItem( row + 13,
                          QVariant( this->ui->tableWidget->item( row, 1 )
                                        ->data( Qt::UserRole )
                                        .toTime() ),
                          writeStream );   //����ʱ��
    }
}

/**
 * @brief   ��ȫ��дdat���ָ�Ĭ��ֵ
 * @warning
 * @todo    �ϴ����ݿ�汾
 */
void SettingWindow::rewriteSettingFile( QFile &f ) {
    qDebug() << "Start rewriting";
    QIODevice::OpenMode originalMode = f.openMode();
    f.close();
    f.open( QIODevice::WriteOnly );
    QDataStream rewriteStream( &f );
    rewriteStream.device()->seek( 0 );
    rewriteStream << MAGIC_NUMBER;      //ħ������
    rewriteStream << CURRENT_VERSION;   //�汾
    // qDebug() << rewriteStream.device()->pos();
    writeSettingItem( 0, QVariant( QDate( 2019, 2, 25 ) ), rewriteStream );
    writeSettingItem( 1, QVariant( static_cast< quint8 >( 20 ) ),
                      rewriteStream );
    //�γ̿�ʼʱ��
    writeSettingItem( 2, QVariant( QTime( 8, 50 ) ), rewriteStream );
    writeSettingItem( 3, QVariant( QTime( 9, 40 ) ), rewriteStream );
    writeSettingItem( 4, QVariant( QTime( 10, 40 ) ), rewriteStream );
    writeSettingItem( 5, QVariant( QTime( 11, 30 ) ), rewriteStream );
    writeSettingItem( 6, QVariant( QTime( 14, 0 ) ), rewriteStream );
    writeSettingItem( 7, QVariant( QTime( 14, 50 ) ), rewriteStream );
    writeSettingItem( 8, QVariant( QTime( 15, 45 ) ), rewriteStream );
    writeSettingItem( 9, QVariant( QTime( 16, 35 ) ), rewriteStream );
    writeSettingItem( 10, QVariant( QTime( 19, 0 ) ), rewriteStream );
    writeSettingItem( 11, QVariant( QTime( 19, 55 ) ), rewriteStream );
    writeSettingItem( 12, QVariant( QTime( 20, 50 ) ), rewriteStream );
    //�γ̽���ʱ��
    writeSettingItem( 13, QVariant( QTime( 9, 35 ) ), rewriteStream );
    writeSettingItem( 14, QVariant( QTime( 10, 25 ) ), rewriteStream );
    writeSettingItem( 15, QVariant( QTime( 11, 25 ) ), rewriteStream );
    writeSettingItem( 16, QVariant( QTime( 12, 15 ) ), rewriteStream );
    writeSettingItem( 17, QVariant( QTime( 14, 45 ) ), rewriteStream );
    writeSettingItem( 18, QVariant( QTime( 15, 35 ) ), rewriteStream );
    writeSettingItem( 19, QVariant( QTime( 16, 30 ) ), rewriteStream );
    writeSettingItem( 20, QVariant( QTime( 17, 20 ) ), rewriteStream );
    writeSettingItem( 21, QVariant( QTime( 19, 45 ) ), rewriteStream );
    writeSettingItem( 22, QVariant( QTime( 20, 40 ) ), rewriteStream );
    writeSettingItem( 23, QVariant( QTime( 21, 35 ) ), rewriteStream );

    f.close();
    f.open( originalMode );
    qDebug() << "End rewriting";
}

/**
 * @brief   ͨ��stream����index������д��dat
 * @warning stream��ҪwriteȨ��
 * @todo    1. Ҫ��һ���������Ȳ������ֽڣ��ֺö�λ��
 *          2. Ҫ�����ϴ����ݿ�
 */
void SettingWindow::writeSettingItem( const qint64 index, QVariant content,
                                      QDataStream &stream ) {
    stream.device()->seek( index * ITEM_SIZE + OFFSET );
    stream << content;
    //������������ȷ���棬�����������ֽ�
    // stream.device()->write(content.toByteArray().left(ITEM_SIZE));
    //���������������ֽڣ���������ȷ����
}

/**
 * @brief   ͨ��stream��dat�ж�ȡ��index������
 * @warning stream��ҪreadȨ��
 * @todo    ��Ҫ���ݿ��ȡ�汾
 */
QVariant SettingWindow::readSettingItem( const qint64 index,
                                         QDataStream &stream ) {
    stream.device()->seek( index * ITEM_SIZE + OFFSET );
    // QByteArray itemData = stream.device()->read(ITEM_SIZE);
    // QDataStream converter(&itemData, QIODevice::ReadWrite);
    // QVariant readItem = QVariant(converter);
    //�������������������ֽڵĻ�����
    return QVariant( stream );
}

/**
 * @brief
 * ͨ��stream��ȡ��index�����ã���ͨ��mainPtr���䴫�ݵ�MainWindow::ClassTable��
 * @note    static
 * @return  ��index�����ö�Ӧ��QVariant
 * @warning ǰ�����Ѿ�ȷ��setting.dat�Ϸ�����stream��readȨ��
 */
QVariant SettingWindow::passOne( const qint64 index, QDataStream &stream,
                                 MainWindow *mainPtr ) {
    ClassTable *tablePtr = mainPtr->childTablePtr;
    switch ( index ) {
        case 0: {   // switch-caseֻ���ڴ��������ܴ�������
            QDate termStartDate     = readSettingItem( 0, stream ).toDate();
            tablePtr->termStartDate = termStartDate;
            return termStartDate;
        }
        case 1: {
            quint8 termTotalWeek =
                readSettingItem( 1, stream ).value< quint8 >();
            tablePtr->termTotalWeek = termTotalWeek;
            return termTotalWeek;
        }
        default: {
            if ( 2 <= index && index <= 23 ) {
                QTime sectionTime = readSettingItem( index, stream ).toTime();
                int   isEnd       = ( static_cast< int >( index ) - 2 ) / 11;
                auto &sectionPair =
                    tablePtr->sectionTime[static_cast< int >( index )
                                          - isEnd * 11 - 2];
                ( isEnd ? sectionPair.second : sectionPair.first ) =
                    sectionTime;
                return sectionTime;
            }
            return QVariant();
        }
    }
}

/**
 * @brief
 * ͨ��stream��ȡ��index�������Ը���SettingWindow�������ݵ�MainWindow::ClassTable��
 * @warning ǰ�����Ѿ�ȷ��setting.dat�Ϸ�����stream��readȨ��
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
        default: {
            if ( 2 <= index && index <= 23 ) {
                int   isEnd    = ( static_cast< int >( index ) - 2 ) / 11;
                QTime itemTime = getSettingItem.toTime();
                qDebug() << itemTime.toString( "h:mm" );
                QTableWidgetItem *item =
                    new QTableWidgetItem( itemTime.toString( "h:mm" ) );
                item->setData( Qt::UserRole, itemTime );
                this->ui->tableWidget->setItem(
                    static_cast< int >( index ) - isEnd * 11 - 2, isEnd, item );
                break;
            }
        }
    }
}

/**
 * @brief   ͨ��stream��ȡdat�Ը������ô��ڣ���������MainWindow::ClassTable
 * @warning ǰ�����Ѿ�ȷ��setting.dat�Ϸ�����stream��readȨ��
 * @todo    �ޣ�
 */
void SettingWindow::updateWindow( QDataStream &stream ) {
    for ( qint64 index = 0; index <= MAX_SETTING_INDEX; ++index ) {
        updateOne( index, stream );
    }
}
/** @overload ���ڲ���stream */
void SettingWindow::updateWindow() {
    QFile settingFile( SETTING_FILE_PATH );
    settingFile.open( QIODevice::ReadOnly | QIODevice::ExistingOnly );
    QDataStream readStream( &settingFile );
    updateWindow( readStream );
}

void SettingWindow::passAll( MainWindow *mainPtr ) {
    QFile settingFile( SETTING_FILE_PATH );

    if ( !settingFile.open(
             QIODevice::ReadOnly ) ) {       //���setting.dat��ȡʧ��
        rewriteSettingFile( settingFile );   //��д�ļ�
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
