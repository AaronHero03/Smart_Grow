#pragma once
#include "Arduino.h"

class Actuator{
protected:
    int pin;
    bool state;

public:
    Actuator(int p) : pin(p){};
    virtual void setup() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    bool getState(){return state;};
};