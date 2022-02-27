#ifndef Calibrate_h
#define Calibrate_h

#include "menu.h"
#include "menumanager.h"

class Calibrate : public IMenu
{
public:
    Calibrate(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

#endif