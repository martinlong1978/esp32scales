#include "multitare.h"
#include "mainmenu.h"
#include "queues.h"

MultiTare::MultiTare(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "NEXT";
    opts[1] = "TARE";
    opts[2] = "MENU";
}

MultiTare::~MultiTare()
{

}

String MultiTare::name()
{
    return "MultiTare";
}

void MultiTare::buttonPress(int button)
{
    if (button == BTN_C)
        _menuManager->setMenu(new MainMenu(_menuManager));
}

void MultiTare::renderDisplay(U8G2 *display)
{

    xQueueReceive(weightStream, &_weight, 10 / portTICK_PERIOD_MS);
    
    display->setFont(SMALL_FONT);
    display->drawStr(MENU_WIDTH, 8, "[0]1 2 3 4 5 6");

    display->setFont(LARGE_FONT);

    char s[16];

    float wt = _menuManager->weightManager.get_units(_weight);
    
    //Serial.printf("Got units: %f\n", wt);

    snprintf(s, sizeof(s), "%0.1fg", wt);

    display->drawStr(127 - display->getStrWidth(s), 45, s);
    

}

