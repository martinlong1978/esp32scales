
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
        delay(1000);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_1, LOW);
        esp_deep_sleep_start();
    }
}

void PowerOff::renderDisplay(U8G2 *display)
{
    display->drawStr(MENU_WIDTH, 28, "Are you sure?");
}
