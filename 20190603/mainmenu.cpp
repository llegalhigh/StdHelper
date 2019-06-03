#include "mainmenu.h"
#include "settingwindow.h"

MainMenu::MainMenu()
{

}

void MainMenu::openSettingWindow()
{
    SettingWindow sw;
    sw.show();
}
