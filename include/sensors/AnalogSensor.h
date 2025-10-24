#pragma once
#include "Arduino.h"
#include "BaseSensor.h"

class AnalogSensor : public Sensor {
protected:
    int pin;
    float rawValue;
    float mapValue;
    unsigned long lastTime;
    long readInterval;

    int minReading;
    int maxReading; 


public:
    AnalogSensor(int pin, long readTime, int minR = 0, int maxR = 4095);
    void setup();
    void calibrate(int low, int high);
    void tick();
    float readRaw();
    float getValue() override;
    virtual void printData() = 0;
};
