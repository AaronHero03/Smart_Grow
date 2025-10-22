#pragma once
#include "Arduino.h"

class GasSensor {
private:
    int pin;
    float value;
    unsigned long lastTime;
    long readTime;

public:
    GasSensor(int pin, long readTime);
    void setup();
    void tick();
    void printData();
    float getData();
};
