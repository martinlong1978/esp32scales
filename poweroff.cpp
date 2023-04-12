
#include "poweroff.h"

PowerOff::PowerOff(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "YES";
    opts[1] = "----";
    opts[2] = "BACK";
}

String PowerOff::name()
{
    return "PowerOff";
}

void PowerOff::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->back();
    if (button == BTN_A)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        _menuManager->enter_sleep();
    }
}

void PowerOff::processWeight(long weight, bool tare)
{
    
}

void PowerOff::renderDisplay(U8G2 *display)
{
    display->drawStr(MENU_WIDTH, 28, "Are you sure?");
}
