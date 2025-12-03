#pragma once
#include "Arduino.h"

class Actuator
{
protected:
    int pin;
    bool state;
    long interval;
    long lastTime;
    String name;

public:
    Actuator(String n, int p, long blinkInterval);

    void setup();
    void activate();
    void deactivate();
    bool getState();
    void blink();
    String getName();
};
