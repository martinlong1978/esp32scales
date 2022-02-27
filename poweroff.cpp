
#include "poweroff.h"

PowerOff::PowerOff(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NXT";
    opts[1] = "TAR";
    opts[2] = "MNU";
}

String PowerOff::name()
{
    return "PowerOff";
}

void PowerOff::buttonPress(int button)
{
}

void PowerOff::renderDisplay(U8G2 *display)
{
}
