#include <Arduino.h>
#include "menu.h"
#include "menumanager.h"
#include "multitare.h"

MenuManager::MenuManager(U8G2 *display)
{
    this->_display = display;
    this->setMenu(new MultiTare(this));
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);
}

void MenuManager::display_loop()
{
    _display->firstPage();
    do
    {
        if (lastbutton > 0)
        {
            _currentMenu->buttonPress(lastbutton);
            lastbutton = -1;
        }
        _display->setFont(COMPACT_FONT);
        const char **men = _currentMenu->options();
        _display->drawStr(0, 16, men[0]);
        _display->drawStr(0, 35, men[1]);
        _display->drawStr(0, 54, men[2]);
        _currentMenu->renderDisplay(_display);
    } while (_display->nextPage());
}

void MenuManager::setMenu(IMenu *menu, bool root)
{
    if (root)
    {
        while (_currentMenu != NULL)
        {
            back();
        }
    }
    menu->setParentMenu(_currentMenu);
    _currentMenu = menu;
}

void MenuManager::back()
{
    IMenu *tmp = _currentMenu;
    _currentMenu = _currentMenu->_parent;
    delete tmp;
    if (_currentMenu != NULL)
    {
        _currentMenu->reactivate();
    }
}