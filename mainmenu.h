
#ifndef MainMenu_h
#define MainMenu_h

#include "menu.h"
#include "menumanager.h"

class MainMenu : public IMenu
{
public:
    MainMenu(MenuManager *menumanager);
    ~MainMenu();
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
private:
    MenuItem *items[3];
    int _currentIndex = 0;
};

#endif