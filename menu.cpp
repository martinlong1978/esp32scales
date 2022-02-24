#include <U8g2lib.h>
#include "menu.h"

void IMenu::setParentMenu(IMenu *parent)
{
    _parent = parent;
}

const char **IMenu::options()
{
    return opts;
}

Main::Main(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NEXT";
    opts[1] = "TARE";
    opts[2] = "MENU";
}

String Main::name()
{
    return "Main";
}

void Main::buttonPress(int button)
{
    if(button == BTN_C)
        _menuManager->setMenu(new Menu(_menuManager));
}

void Main::renderDisplay(U8G2 *display)
{
    display->setFont(SMALL_FONT);
    display->drawStr(MENU_WIDTH, 8, "[0]1 2 3 4 5 6");

    display->setFont(LARGE_FONT);
    display->drawStr(MENU_WIDTH, 40, "1.256kg");
}

Menu::Menu(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NEXT";
    opts[1] = "SLCT";
    opts[2] = "BACK";
}

void Menu::buttonPress(int button)
{
    if(button == BTN_C)
        _menuManager->back();
}

String Menu::name()
{
    return "Menu";
}

void Menu::renderDisplay(U8G2 *display)
{
    display->setFont(SMALL_FONT);
    display->drawStr(MENU_WIDTH, 8, "Calibrate");
    display->drawStr(MENU_WIDTH, 20, "Settings");
}

MultiTare::MultiTare(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NXT";
    opts[1] = "TAR";
    opts[2] = "MNU";
}

String MultiTare::name()
{
    return "MultiTare";
}

void MultiTare::buttonPress(int button)
{
}

void MultiTare::renderDisplay(U8G2 *display)
{
}

Calibrate::Calibrate(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NXT";
    opts[1] = "TAR";
    opts[2] = "MNU";
}

String Calibrate::name()
{
    return "Calibrate";
}

void Calibrate::buttonPress(int button)
{
}

void Calibrate::renderDisplay(U8G2 *display)
{
}

PowerOff::PowerOff(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NXT";
    opts[1] = "TAR";
    opts[2] = "MNU";
}

String PowerOff::name()
{
    return "PowerOff";
}

void PowerOff::buttonPress(int button)
{
}

void PowerOff::renderDisplay(U8G2 *display)
{
}
