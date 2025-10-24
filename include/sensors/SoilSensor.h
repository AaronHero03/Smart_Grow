#pragma once
#include "Arduino.h"
#include "AnalogSensor.h"

class SoilSensor : public AnalogSensor {
public:
    SoilSensor(int pin, long readInterval) : AnalogSensor(pin, readInterval) {};

    void printData() override {
        Serial.print("Soil humidity level: ");
        Serial.println(mapValue);
    }
};
