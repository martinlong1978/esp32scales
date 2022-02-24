#include "menu.h"
#include "menumanager.h"
#include <Arduino.h>

MenuManager::MenuManager(U8G2 *display)
{
    this->_display = display;
    this->setMenu(new Main(this));
    pinMode(1, INPUT_PULLUP);
    pinMode(38, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);
}

void MenuManager::display_loop()
{
    _display->firstPage();
    do
    {
        if (digitalRead(1) == LOW)
            _currentMenu->buttonPress(1);
        if (digitalRead(38) == LOW)
            _currentMenu->buttonPress(2);
        if (digitalRead(33) == LOW)
        {
            back();
        };
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
    }
}