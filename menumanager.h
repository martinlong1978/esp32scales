#ifndef MenuManager_h
#define MenuManager_h

class IMenu;

#include <U8g2lib.h>
#include "menu.h"

#define SAMPLES 5


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
    int _samplePointer = 0;
    long _samples[SAMPLES];
    bool _tare;

};

class MenuManager
{
public:
    MenuManager(U8G2 *display);
    void display_loop();
    void setMenu(IMenu *menu, bool root = false);
    void back();
    volatile int lastbutton = 0;
    volatile bool pressed = false;
    volatile bool isLongPress = false;
    WeightManager weightManager;
    void enter_sleep();

private:
    U8G2 *_display;
    IMenu *_currentMenu;
};

#endif