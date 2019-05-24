#ifndef MAINMENU_H
#define MAINMENU_H

#include "ui_mainwindow.h"


class MainMenu : public Ui_MainWindow {
    Q_OBJECT

public:
    MainMenu();

public slots:
    void openSettingWindow();
};

#endif   // MAINMENU_H
