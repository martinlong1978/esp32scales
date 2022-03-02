#ifndef MenuManager_h
#define MenuManager_h

class IMenu;

#include <U8g2lib.h>
#include "menu.h"

class MenuManager
{
public:
    MenuManager(U8G2 *display);
    void display_loop();
    void setMenu(IMenu *menu, bool root = false);
    void back();
    int lastbutton = 0;

private:
    U8G2 *_display;
    IMenu *_currentMenu;
};

#endif