#ifndef Calibrate_h
#define Calibrate_h

#include "menu.h"
#include "menumanager.h"
#include "queues.h"

class Calibrate : public IMenu
{
public:
    Calibrate(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
    virtual void processWeight(long weight, bool tare);

private:
    int _state = 0;
    int _samplePointer = 0;
    long _samples[SAMPLES];
};

#endif