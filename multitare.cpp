#include "multitare.h"
#include "mainmenu.h"

MultiTare::MultiTare(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NEXT";
    opts[1] = "TARE";
    opts[2] = "MENU";
}

String MultiTare::name()
{
    return "MultiTare";
}

void MultiTare::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->setMenu(new MainMenu(_menuManager));
}

void MultiTare::renderDisplay(U8G2 *display)
{
    
    display->setFont(SMALL_FONT);
    display->drawStr(MENU_WIDTH, 8, "[0]1 2 3 4 5 6");

    display->setFont(LARGE_FONT);
    display->drawStr(MENU_WIDTH, 40, "1.256kg");

}

