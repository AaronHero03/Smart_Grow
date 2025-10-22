#pragma once
#include "Arduino.h"

class SoilSensor {
private:
    int pin;
    float value;
    unsigned long lastTime;
    long readTime;

public:
    SoilSensor(int pin, long readTime);
    void setup();
    void tick();
    void printData();
    float getData();
};
