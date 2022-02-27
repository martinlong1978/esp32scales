#ifndef Poweroff_h
#define Poweroff_h

#include "menu.h"
#include "menumanager.h"

class PowerOff : public IMenu
{
public:
    PowerOff(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

#endif