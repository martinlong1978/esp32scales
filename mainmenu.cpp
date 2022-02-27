#include "mainmenu.h"
#include "calibrate.h"
#include "multitare.h"
#include "poweroff.h"

MainMenu::MainMenu(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NEXT";
    opts[1] = "SLCT";
    opts[2] = "BACK";
    items[0] = new MenuItem{"Calibrate", [menumanager]()
                            { return new Calibrate(menumanager); }};
    items[1] = new MenuItem{"Multi-tare", [menumanager]()
                            { return new MultiTare(menumanager); }};
    items[2] = new MenuItem{"Power Off", [menumanager]()
                            { return new PowerOff(menumanager); }};
}

MainMenu::~MainMenu()
{
    // Delete menu items (any constructed menus are dealt with by the manager)
    for (int i = 0; i < 3; i++)
    {
        delete items[i];
    }
}

void MainMenu::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->back();
}

String MainMenu::name()
{
    return "Menu";
}

void MainMenu::renderDisplay(U8G2 *display)
{
    display->setFont(SMALL_FONT);
    // display->drawStr(MENU_WIDTH, 8, "Calibrate");
    // display->drawStr(MENU_WIDTH, 20, "Settings");
    int h = 64 / 4;

    for(int i =0; i < 3; i++){
        int pos = (h * (i + 1)) - ((h - 8) / 2);
        display->drawStr(MENU_WIDTH, pos, items[i]->name);
    }
}
