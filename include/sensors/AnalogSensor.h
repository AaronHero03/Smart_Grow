#pragma once
#include "Arduino.h"
#include "Sensor.h"

class AnalogSensor : public Sensor
{
protected:
    int pin;
    long lastTime;
    long readInterval;

    float rawValue;
    float mapValue;

    int minReading;
    int maxReading;

    String name;

public:
    AnalogSensor(String name, int pin, long readTime, int minR = 0, int maxR = 4095);
    void setup() override;
    void calibrate(int low, int high);

    void tick() override;
    float readRaw();

    String getName() override;
    float getValue() override;

    void printData();
};
