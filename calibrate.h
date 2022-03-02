#ifndef Calibrate_h
#define Calibrate_h

#include "menu.h"
#include "menumanager.h"
#include "queues.h"

#define SAMPLES 5

class Calibrate : public IMenu
{
public:
    Calibrate(MenuManager *menumanager);
    virtual void renderDisplay(U8G2 *display);
    virtual void buttonPress(int button);
    virtual String name();
private:
    int _state = 0;
    void processWeight(long weight);
    int _samplePointer = 0;
    long _samples[SAMPLES];
};

#endif