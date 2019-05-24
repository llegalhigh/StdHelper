#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QDebug>
//数据存储
#include <QVariant>
//通知
#include <QMessageBox>

/*
 * 设置文件: setting.dat
 *
 * 设置项:
 *  index    name & description & type
 *  0        本学期从什么时候开始(QDate)
 *  1        本学期有多少周(quint8)
 *
 * 文件内容: 4字节魔术数字+4字节版本号+100字节设置0+100字节设置1+...
 */

static constexpr quint32 MAGIC_NUMBER = 0xBAD00CAB; //魔术数字
static constexpr qint32 CURRENT_VERSION = 100;      //版本
static constexpr qint64 OFFSET = 8;                 //魔术数字和版本号占8字节
static constexpr qint64 ITEM_SIZE = 100;            //设置占的字节数
const QString SETTING_FILE_PATH = "D:/setting.dat"; //设置文件存储的路径

//窗口构造函数
SettingWindow::SettingWindow(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::SettingWindow) {
    ui->setupUi(this);

    //设置文件:setting.dat
    QFile settingFile(SETTING_FILE_PATH);

    if (!settingFile.open(QIODevice::ReadOnly)) { //如果setting.dat读取失败
        qDebug() << "[[ If";
        //重写文件
        rewriteSettingFile(settingFile);
        updateWindow();
    } else {
        /*
         * 二进制文件读写参考
         * https://www.devbean.net/2013/01/qt-study-road-2-binary-file-io/
         */
        qDebug() << "[[ Else";
        QDataStream readStream(&settingFile);

        //检查魔术数字
        quint32 readMagicNumber;
        readStream >> readMagicNumber;
        qDebug() << "[[ readMagicNumber: " << readMagicNumber;
        if (readMagicNumber != MAGIC_NUMBER) {
            rewriteSettingFile(settingFile);
        } else {
            //检查版本
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

//窗口析构函数
SettingWindow::~SettingWindow() {
    delete ui;
}

//槽，保存界面上所有设置项
void SettingWindow::saveAll() {
    QFile settingFile(SETTING_FILE_PATH);
    settingFile.open(QIODevice::ReadWrite);

    QDataStream writeStream(&settingFile);

    writeSettingItem(0, QVariant(this->ui->termStartDateEdit->date()), writeStream);
    writeSettingItem(1, QVariant(this->ui->totalWeekBox->value()), writeStream);
}

//重写setting.dat
void SettingWindow::rewriteSettingFile(QFile &f) {
    qDebug() << "Start rewriting";
    QIODevice::OpenMode originalMode = f.openMode();
    f.close();
    f.open(QIODevice::WriteOnly);
    QDataStream rewriteStream(&f);
    rewriteStream.device()->seek(0);
    rewriteStream << MAGIC_NUMBER;    //魔术数字
    rewriteStream << CURRENT_VERSION; //版本
    //qDebug() << rewriteStream.device()->pos();
    writeSettingItem(0, QVariant(QDate(2019, 2, 25)), rewriteStream);
    writeSettingItem(1, QVariant((quint8)20), rewriteStream);
    f.close();
    f.open(originalMode);
    qDebug() << "End rewriting";
}

//前提：stream需要write权限
void SettingWindow::writeSettingItem(qint64 index, QVariant content, QDataStream &stream) {
    stream.device()->seek(index * ITEM_SIZE + OFFSET);
    //stream << content;
    //上面这样虽然简单，但不能限制字节
    //TO-DO: 要想一个方法，既不限制字节，又好定位
    stream.device()->write(content.toByteArray().left(ITEM_SIZE));
}

//前提：stream需要read权限
//读取有问题，明天搞
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

//注意：本函数使用前提是已经确保setting.dat合法，stream有read权限
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
