#include "calibrate.h"

Calibrate::Calibrate(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NXT";
    opts[1] = "TAR";
    opts[2] = "MNU";
}

String Calibrate::name()
{
    return "Calibrate";
}

void Calibrate::buttonPress(int button)
{
}

void Calibrate::renderDisplay(U8G2 *display)
{
}