#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
//文件处理
#include <QBitArray>
#include <QDataStream>
#include <QFile>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void saveAll();

    void on_applyButton_clicked();
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::SettingWindow *ui;

    static void rewriteSettingFile(QFile &);
    static void writeSettingItem(qint64, QVariant, QDataStream &);
    static QVariant readSettingItem(qint64, QDataStream &);

    void updateWindow(QDataStream &stream);
    void updateWindow();
};

#endif // SETTINGWINDOW_H
