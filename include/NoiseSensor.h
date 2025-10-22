#pragma once
#include "Arduino.h"

class NoiseSensor {
private:
    int pin;
    float value;
    unsigned long lastTime;
    long readTime;

public:
    NoiseSensor(int pin, long readTime);
    void setup();
    void tick();
    void printData();
    float getData();
};
