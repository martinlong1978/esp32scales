#include <Arduino.h>
#include <ADS1232.h>
#include "menu.h"
#include "menumanager.h"
#include "multitare.h"
#include <EEPROM.h>
#include "eepromext.h"
#include "queues.h"

float WeightManager::get_units(long raw)
{
    return (raw - _offset) / _factor;
}

float WeightManager::get_units()
{
    return get_units(_weight);
}

void WeightManager::set_factor(float factor)
{
    _factor = factor;
}

void WeightManager::set_offset(long offset)
{
    _offset = offset;
    Serial.printf("Offset is %d\n", _offset);
}

void WeightManager::set_factor(float weight, long raw)
{
    _factor = (raw - _offset) / weight;
    Serial.printf("Factor is %f\n", _factor);
}

void WeightManager::save()
{
    Serial.println("Saving");
    EEPROM_writeAnything(0, _factor);
    Serial.println("Saved");
}

void WeightManager::checkWeight(IMenu *callback)
{
    while (uxQueueMessagesWaiting(weightStream) > 0)
    {
        xQueueReceive(weightStream, &_weight, 10 / portTICK_PERIOD_MS);
        callback->processWeight(_weight);
    }
}

void WeightManager::load()
{
    EEPROM_readAnything(0, _factor);
}

WeightManager::WeightManager()
{
}

MenuManager::MenuManager(U8G2 *display)
{
    this->_display = display;
    this->setMenu(new MultiTare(this));
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);
}

void MenuManager::display_loop()
{
    _display->firstPage();
    do
    {
        if (lastbutton > 0)
        {
            _currentMenu->buttonPress(lastbutton);
            lastbutton = -1;
        }
        _display->setFont(COMPACT_FONT);
        const char **men = _currentMenu->options();
        _display->drawStr(0, 16, men[0]);
        _display->drawStr(0, 35, men[1]);
        _display->drawStr(0, 54, men[2]);
        _currentMenu->renderDisplay(_display);
    } while (_display->nextPage());
}

void MenuManager::setMenu(IMenu *menu, bool root)
{
    if (root)
    {
        while (_currentMenu != NULL)
        {
            back();
        }
    }
    menu->setParentMenu(_currentMenu);
    _currentMenu = menu;
}

void MenuManager::back()
{
    IMenu *tmp = _currentMenu;
    _currentMenu = _currentMenu->_parent;
    delete tmp;
    if (_currentMenu != NULL)
    {
        _currentMenu->reactivate();
    }
}