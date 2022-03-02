#include "calibrate.h"

Calibrate::Calibrate(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "----";
    opts[1] = "----";
    opts[2] = "BACK";
}

String Calibrate::name()
{
    return "Calibrate";
}

void Calibrate::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->back();
}

void Calibrate::renderDisplay(U8G2 *display)
{
}