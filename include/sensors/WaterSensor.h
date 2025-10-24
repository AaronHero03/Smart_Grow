#pragma once
#include "Arduino.h"
#include "AnalogSensor.h"

class WaterSensor : public AnalogSensor {
public:
    WaterSensor(int pin, long readInterval) : AnalogSensor(pin, readInterval) {};

    void printData() override {
        Serial.print("Water level: ");
        Serial.println(mapValue);
    }
};
