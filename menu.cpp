#include "menu.h"
#include <U8g2lib.h>

void IMenu::setParentMenu(IMenu *parent)
{
    _parent = parent;
}

Main::Main(MenuManager *menumanager)
{
    _menuManager = menumanager;
}

String Main::name(){
    return "Main";
}

void Main::buttonPress(int button)
{
    _menuManager->setMenu(new Menu(_menuManager));
}

void Main::renderDisplay(U8G2 *display)
{
    display->setFont(u8g2_font_ncenR08_tf);
    display->drawStr(0, 8, "[0]  1   2   3   4   5   6  ");

    display->setFont(u8g2_font_logisoso24_tf);
    display->drawStr(0, 40, "1.256kg");
}

Menu::Menu(MenuManager *menumanager)
{
    _menuManager = menumanager;
}

void Menu::buttonPress(int button)
{
}

String Menu::name(){
    return "Menu";
}

void Menu::renderDisplay(U8G2 *display)
{
    display->setFont(u8g2_font_ncenR08_tf);
    display->drawStr(0, 8, "Calibrate");
    display->drawStr(0, 20, "Settings");
}

MultiTare::MultiTare(MenuManager *menumanager)
{
    _menuManager = menumanager;
}

String MultiTare::name(){
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
}

String Calibrate::name(){
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
}

String PowerOff::name(){
    return "PowerOff";
}

void PowerOff::buttonPress(int button)
{
}

void PowerOff::renderDisplay(U8G2 *display)
{
}
