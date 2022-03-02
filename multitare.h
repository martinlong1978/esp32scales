#ifndef MultiTare_h
#define MultiTare_h

#include "menu.h"
#include "menumanager.h"

class MultiTare : public IMenu
{
public:
    MultiTare(MenuManager *menumanager);
    ~MultiTare();
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
private:
    long _weight;
};

#endif