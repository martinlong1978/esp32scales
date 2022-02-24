#ifndef Menu_h
#define Menu_h

#include <U8g2lib.h>
#include "menumanager.h"

class IMenu
{

public:
    IMenu *_parent;
    MenuManager *_menuManager;
    virtual void renderDisplay(U8G2 *display) = 0;
    virtual void buttonPress(int button) = 0;
    void setParentMenu(IMenu *parent);
    virtual String name() = 0;
};

class MultiTare : public IMenu
{
public:
    MultiTare(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

class Calibrate : public IMenu
{
public:
    Calibrate(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

class Menu : public IMenu
{
public:
    Menu(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

class PowerOff : public IMenu
{
public:
    PowerOff(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

class Main : public IMenu
{
public:
    Main(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
};

#endif
