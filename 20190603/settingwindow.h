#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include "mainwindow.h"

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

    friend class MainWindow;

public:
    explicit SettingWindow( MainWindow *parentMain, QWidget *parent = nullptr );
    ~SettingWindow();

private slots:
    void saveAll();

    void on_applyButton_clicked();
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::SettingWindow *ui;
    MainWindow *       mainWindowPtr;

    static constexpr qint64 MAX_SETTING_INDEX = 23;   // index目前最大值

    static void     rewriteSettingFile( QFile & );
    static void     writeSettingItem( const qint64, QVariant, QDataStream & );
    static QVariant readSettingItem( const qint64, QDataStream & );

    static QVariant passOne( const qint64, QDataStream &, MainWindow * );
    void            updateOne( const qint64, QDataStream & );
    void            updateWindow( QDataStream & );
    void            updateWindow();

    static void passAll( MainWindow * );
};

#endif   // SETTINGWINDOW_H
