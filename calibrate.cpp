#include "calibrate.h"

Calibrate::Calibrate(MenuManager *menumanager)
{
    _menuManager = menumanager;
    opts[0] = "";
    opts[1] = "--->";
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
    if (button == BTN_B)
    {
        switch (_state)
        {
        case 0:
            _menuManager->weightManager.tare();
            _state++;
            break;
        case 2:
            _samplePointer = 0;
            xQueueReset(weightStream);
            _state++;
            break;
        }
    }
}

void Calibrate::processWeight(long weight, bool tare)
{
    switch (_state)
    {
    case 1:
        if (tare)
            _state++;
    case 3:
        _samples[_samplePointer++] = weight;
        if (_samplePointer >= SAMPLES)
        {
            _samplePointer = 0;
            long total = 0;
            for (int i = 0; i < SAMPLES; i++)
            {
                total += _samples[i];
            }
            Serial.println("Setting factor");
            _menuManager->weightManager.set_factor(500.0, total / SAMPLES);
            Serial.println("Saving");
            _menuManager->weightManager.save();
            Serial.println("Back");
            _menuManager->back();
            Serial.println("Done");
        }
        break;
    }
}

void Calibrate::renderDisplay(U8G2 *display)
{
    _menuManager->weightManager.checkWeight(this);
    const char *message;
    switch (_state)
    {
    case 0:
        message = "Set zero";
        break;
    case 1:
        message = "Zeroing...";
        break;
    case 2:
        message = "Place 500g";
        break;
    case 3:
        message = "Calibrating...";
        break;
    }
    display->drawStr(MENU_WIDTH, 32, message);
}