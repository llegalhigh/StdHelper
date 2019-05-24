#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QDebug>
//���ݴ洢
#include <QVariant>
//֪ͨ
#include <QMessageBox>

/*
 * �����ļ�: setting.dat
 *
 * ������:
 *  index    name & description & type
 *  0        ��ѧ�ڴ�ʲôʱ��ʼ(QDate)
 *  1        ��ѧ���ж�����(quint8)
 *
 * �ļ�����: 4�ֽ�ħ������+4�ֽڰ汾��+100�ֽ�����0+100�ֽ�����1+...
 */

static constexpr quint32 MAGIC_NUMBER = 0xBAD00CAB; //ħ������
static constexpr qint32 CURRENT_VERSION = 100;      //�汾
static constexpr qint64 OFFSET = 8;                 //ħ�����ֺͰ汾��ռ8�ֽ�
static constexpr qint64 ITEM_SIZE = 100;            //����ռ���ֽ���
const QString SETTING_FILE_PATH = "D:/setting.dat"; //�����ļ��洢��·��

//���ڹ��캯��
SettingWindow::SettingWindow(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::SettingWindow) {
    ui->setupUi(this);

    //�����ļ�:setting.dat
    QFile settingFile(SETTING_FILE_PATH);

    if (!settingFile.open(QIODevice::ReadOnly)) { //���setting.dat��ȡʧ��
        qDebug() << "[[ If";
        //��д�ļ�
        rewriteSettingFile(settingFile);
        updateWindow();
    } else {
        /*
         * �������ļ���д�ο�
         * https://www.devbean.net/2013/01/qt-study-road-2-binary-file-io/
         */
        qDebug() << "[[ Else";
        QDataStream readStream(&settingFile);

        //���ħ������
        quint32 readMagicNumber;
        readStream >> readMagicNumber;
        qDebug() << "[[ readMagicNumber: " << readMagicNumber;
        if (readMagicNumber != MAGIC_NUMBER) {
            rewriteSettingFile(settingFile);
        } else {
            //���汾
            qint32 readVersion;
            readStream >> readVersion;
            qDebug() << "[[ readVersion: " << readVersion;
            if (readVersion < CURRENT_VERSION) {
                rewriteSettingFile(settingFile);

                QMessageBox oldFileMsgBox;
                oldFileMsgBox.setText(tr("Existed setting file is of old version."));
                oldFileMsgBox.setInformativeText(tr("It has been replaced with a default new one."));
                oldFileMsgBox.setStandardButtons(QMessageBox::Ok);

                oldFileMsgBox.exec();
            }
            readStream.setVersion(QDataStream::Qt_5_12);

            updateWindow(readStream);
        }
    }

    settingFile.close();
}

//������������
SettingWindow::~SettingWindow() {
    delete ui;
}

//�ۣ��������������������
void SettingWindow::saveAll() {
    QFile settingFile(SETTING_FILE_PATH);
    settingFile.open(QIODevice::ReadWrite);

    QDataStream writeStream(&settingFile);

    writeSettingItem(0, QVariant(this->ui->termStartDateEdit->date()), writeStream);
    writeSettingItem(1, QVariant(this->ui->totalWeekBox->value()), writeStream);
}

//��дsetting.dat
void SettingWindow::rewriteSettingFile(QFile &f) {
    qDebug() << "Start rewriting";
    QIODevice::OpenMode originalMode = f.openMode();
    f.close();
    f.open(QIODevice::WriteOnly);
    QDataStream rewriteStream(&f);
    rewriteStream.device()->seek(0);
    rewriteStream << MAGIC_NUMBER;    //ħ������
    rewriteStream << CURRENT_VERSION; //�汾
    //qDebug() << rewriteStream.device()->pos();
    writeSettingItem(0, QVariant(QDate(2019, 2, 25)), rewriteStream);
    writeSettingItem(1, QVariant((quint8)20), rewriteStream);
    f.close();
    f.open(originalMode);
    qDebug() << "End rewriting";
}

//ǰ�᣺stream��ҪwriteȨ��
void SettingWindow::writeSettingItem(qint64 index, QVariant content, QDataStream &stream) {
    stream.device()->seek(index * ITEM_SIZE + OFFSET);
    //stream << content;
    //����������Ȼ�򵥣������������ֽ�
    //TO-DO: Ҫ��һ���������Ȳ������ֽڣ��ֺö�λ
    stream.device()->write(content.toByteArray().left(ITEM_SIZE));
}

//ǰ�᣺stream��ҪreadȨ��
//��ȡ�����⣬�����
QVariant SettingWindow::readSettingItem(qint64 index, QDataStream &stream) {
    stream.device()->seek(index * ITEM_SIZE + OFFSET);
    QByteArray itemData = stream.device()->read(ITEM_SIZE);
    qDebug() << itemData;
    QDataStream converter(&itemData, QIODevice::ReadOnly);
    QVariant readItem;
    converter >> readItem;
    qDebug() << readItem.isNull();
    return readItem;
}

//ע�⣺������ʹ��ǰ�����Ѿ�ȷ��setting.dat�Ϸ���stream��readȨ��
void SettingWindow::updateWindow(QDataStream &stream) {
    QVariant readItem;

    readItem = readSettingItem(0, stream);
    QDate termStartDate = readItem.value<QDate>();
    this->ui->termStartDateEdit->setDate(termStartDate);

    readItem = readSettingItem(1, stream);
    quint8 termTotalWeek = readItem.value<quint8>();
    this->ui->totalWeekBox->setValue(termTotalWeek);
}
void SettingWindow::updateWindow() {
    QFile settingFile(SETTING_FILE_PATH);
    settingFile.open(QIODevice::ReadOnly | QIODevice::ExistingOnly);
    QDataStream readStream(&settingFile);
    updateWindow(readStream);
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
