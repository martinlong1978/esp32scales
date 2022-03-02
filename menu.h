#ifndef Menu_h
#define Menu_h

#include <U8g2lib.h>
#include "menumanager.h"
#include <functional>

#define MENU_WIDTH 26
#define SMALL_FONT u8g2_font_b12_t_japanese1
#define LARGE_FONT u8g2_font_logisoso24_tf
#define COMPACT_FONT u8g2_font_finderskeepers_tr

#define BTN_A 1
#define BTN_B 38
#define BTN_C 33
#define SCREEN_HEIGHT 64;

class IMenu
{

public:
    IMenu *_parent;
    MenuManager *_menuManager;
    virtual void renderDisplay(U8G2 *display) = 0;
    virtual void buttonPress(int button) = 0;
    void setParentMenu(IMenu *parent);
    virtual String name() = 0;
    const char **options();
    virtual void reactivate();
    virtual void processWeight(long weight);

protected:
    const char *opts[3];
};

struct MenuItem
{
    const char *name;
    std::function<void()> lamb;
};
#endif
