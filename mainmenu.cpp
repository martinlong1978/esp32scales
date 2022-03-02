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
                            { menumanager->setMenu(new Calibrate(menumanager)); }};
    items[1] = new MenuItem{"Multi-tare", [menumanager]()
                            {  menumanager->setMenu(new MultiTare(menumanager), true); }};
    items[2] = new MenuItem{"Power Off", [menumanager]()
                            {  menumanager->setMenu(new PowerOff(menumanager)); }};
}

MainMenu::~MainMenu()
{
    // Delete menu items (any constructed menus are dealt with by the manager)
    for (int i = 0; i < ITEMCOUNT; i++)
    {
        delete items[i];
    }
}

void MainMenu::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->back();
    if (button == BTN_A)
        if(++_currentIndex >= ITEMCOUNT)
            _currentIndex = 0;
    if(button == BTN_B)
        items[_currentIndex]->lamb();
}

String MainMenu::name()
{
    return "Menu";
}

void MainMenu::renderDisplay(U8G2 *display)
{
    display->setFont(SMALL_FONT);
    int h = 64 / (ITEMCOUNT + 1);

    for (int i = 0; i < ITEMCOUNT; i++)
    {
        int pos = (h * (i + 1)) - ((h - 8) / 2);
        if (i == _currentIndex)
        {
            display->drawBox(MENU_WIDTH, pos - 9, 127 - MENU_WIDTH, 10);
            display->setDrawColor(0);
        }
        display->drawStr(MENU_WIDTH, pos, items[i]->name);
        display->setDrawColor(1);
    }
}

