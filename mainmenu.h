
#ifndef MainMenu_h
#define MainMenu_h

#include "menu.h"
#include "menumanager.h"

#define ITEMCOUNT 3

class MainMenu : public IMenu
{
public:
    MainMenu(MenuManager *menumanager);
    ~MainMenu();
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
    virtual void processWeight(long weight, bool tare);
private:
    MenuItem *items[ITEMCOUNT];
    int _currentIndex = 0;
};

#endif