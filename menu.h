#ifndef Menu_h
#define Menu_h

#include <U8g2lib.h>
#include "menumanager.h"


#define MENU_WIDTH 26
#define SMALL_FONT u8g2_font_b12_t_japanese1
#define LARGE_FONT u8g2_font_logisoso24_tf
#define COMPACT_FONT u8g2_font_finderskeepers_tr

#define BTN_A 1
#define BTN_B 38
#define BTN_C 33



class IMenu
{

public:
    IMenu *_parent;
    MenuManager *_menuManager;
    virtual void renderDisplay(U8G2 *display) = 0;
    virtual void buttonPress(int button) = 0;
    void setParentMenu(IMenu *parent);
    virtual String name() = 0;
    const char ** options();
protected: 
    const char *opts[3] = {"NXT","TAR","MEN"};


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
