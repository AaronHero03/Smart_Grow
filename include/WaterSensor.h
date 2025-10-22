#pragma once
#include "Arduino.h"

class WaterSensor{
private:
    int pin;
    float value;
    
    unsigned long lastTime;
    long readTime;
public:
    WaterSensor(int pin, long readTime);
        
    void setup();
    void tick();
    void printData();
    
    float getData();
};