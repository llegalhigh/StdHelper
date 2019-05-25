#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QDebug>

//���ݴ洢
#include <QVariant>

//֪ͨ
#include <QMessageBox>


/*****************************************************************************
 * �����ļ�: setting.dat
 *
 * ������:
 *  index    name & description & type
 *  0        termStartDate, ��ѧ�ڴ�ʲôʱ��ʼ(QDate)
 *  1        termTotalWeek, ��ѧ���ж�����(quint8)
 *
 * �ļ�����: 4�ֽ�ħ������+4�ֽڰ汾��+100�ֽ�����0+100�ֽ�����1+...
 *
 * �������ļ���д�ο���
 * https://www.devbean.net/2013/01/qt-study-road-2-binary-file-io/
 *****************************************************************************/

static constexpr quint32 MAGIC_NUMBER    = 0xBAD00CAB;   //ħ������
static constexpr qint32  CURRENT_VERSION = 100;          //�汾
static constexpr qint64  OFFSET   = 8;   //ħ�����ֺͰ汾��ռ8�ֽ�
static constexpr qint64 ITEM_SIZE = sizeof( QVariant );   //����ռ���ֽ���
const QString SETTING_FILE_PATH = "D:/setting.dat";   //�����ļ��洢��·��

/** ���ڹ��캯�� */
SettingWindow::SettingWindow( MainWindow *parentMain, QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::SettingWindow ),
      mainWindowPtr( parentMain ) {
    qDebug() << "Setting window opened";
    ui->setupUi( this );

    ui->termStartDateEdit->setMinimumDate(
        QDate::currentDate().addYears( -2 ) );
    ui->termStartDateEdit->setMaximumDate( QDate::currentDate().addYears( 2 ) );

    //�����ļ�:setting.dat
    QFile settingFile( SETTING_FILE_PATH );

    if ( !settingFile.open(
             QIODevice::ReadOnly ) ) {       //���setting.dat��ȡʧ��
        rewriteSettingFile( settingFile );   //��д�ļ�(ѯ��?)
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
    writeSettingItem( 1, QVariant( (quint8)20 ), rewriteStream );
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
 * @brief   ͨ��stream��ȡ��index�����ã���ͨ��mainPtr���䴫�ݵ�MainWindow��
 * @note    static
 * @return  ��index�����ö�Ӧ��QVariant
 * @warning ǰ�����Ѿ�ȷ��setting.dat�Ϸ�����stream��readȨ��
 */
QVariant SettingWindow::passOne( const qint64 index, QDataStream &stream,
                                 MainWindow *mainPtr ) {
    switch ( index ) {
        case 0: {   // switch-caseֻ���ڴ��������ܴ�������
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
 * @brief   ͨ��stream��ȡ��index�������Ը���SettingWindow�������ݵ�MainWindow��
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
    }
}

/**
 * @brief   ͨ��stream��ȡdat�Ը������ô��ڣ���������MainWindow
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
        rewriteSettingFile( settingFile );   //��д�ļ�(ѯ��?)
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
