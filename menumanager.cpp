#include "menu.h"
#include "menumanager.h"
#include <Arduino.h>

MenuManager::MenuManager(U8G2 *display)
{
    this->_display = display;
    this->setMenu(new Main(this));
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

void MenuManager::setMenu(IMenu *menu)
{
    menu->setParentMenu(_currentMenu);
    _currentMenu = menu;
}

void MenuManager::back()
{
    if (_currentMenu->_parent != NULL)
    {
        IMenu *tmp = _currentMenu;
        _currentMenu = _currentMenu->_parent;
        delete tmp;
        _currentMenu->reactivate();
    }
}