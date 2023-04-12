#include <Arduino.h>
#include <ADS1232.h>
#include "menu.h"
#include "menumanager.h"
#include "multitare.h"
#include <EEPROM.h>
#include "eepromext.h"
#include "queues.h"
#include "esp_sleep.h"

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
}

void WeightManager::set_factor(float weight, long raw)
{
    _factor = (raw - _offset) / weight;
}

void WeightManager::save()
{
    EEPROM_writeAnything(0, _factor);
}

void WeightManager::checkWeight(IMenu *callback)
{
    while (uxQueueMessagesWaiting(weightStream) > 0)
    {
        xQueueReceive(weightStream, &_weight, 10 / portTICK_PERIOD_MS);
        if (!_tare)
        {
            _samples[_samplePointer++] = _weight;
            if (_samplePointer >= SAMPLES)
            {
                _samplePointer = 0;
                long total = 0;
                for (int i = 0; i < SAMPLES; i++)
                {
                    Serial.printf("Value: %d - %d\n", i, _samples[i]);
                    total += _samples[i];
                }
                _offset = total / SAMPLES;
                _tare = true;
            }
        }
        callback->processWeight(_weight, _tare);
    }
}

void WeightManager::tare()
{
    xQueueReset(weightStream);
    _tare = false;
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

void MenuManager::enter_sleep()
{
    _display->setPowerSave(1);
    gpio_hold_en(GPIO_NUM_5);
    gpio_deep_sleep_hold_en();

    esp_sleep_enable_ext0_wakeup(GPIO_NUM_1, LOW);
    esp_deep_sleep_start();
}

void MenuManager::display_loop()
{
    _display->firstPage();
    do
    {
        //        if (portTRY_ENTER_CRITICAL(&timerMux, portMUX_TRY_LOCK) == pdPASS)
        if (lastbutton > 0 && !pressed)
        {
            if (isLongPress)
            {
                _currentMenu->longButtonPress(lastbutton);
            }
            else
            {
                _currentMenu->buttonPress(lastbutton);
            }
            lastbutton = 0;
        };
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