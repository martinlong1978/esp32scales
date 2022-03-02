#ifndef MenuManager_h
#define MenuManager_h

class IMenu;

#include <U8g2lib.h>
#include "menu.h"

class WeightManager
{
public:
    WeightManager();
    void set_factor(float weight, long raw);
    void set_factor(float factor);
    void set_offset(long offsset);
    float get_units(long raw);
    float get_units();
    void tare();
    void load();
    void save();
    void checkWeight(IMenu *callback);

private:
    float _factor = 1.0;
    long _offset = 0;
    long _weight = 0;

};

class MenuManager
{
public:
    MenuManager(U8G2 *display);
    void display_loop();
    void setMenu(IMenu *menu, bool root = false);
    void back();
    int lastbutton = 0;
    WeightManager weightManager;

private:
    U8G2 *_display;
    IMenu *_currentMenu;
};

#endif