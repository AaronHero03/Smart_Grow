#pragma once
#include "Arduino.h"
#include "AnalogSensor.h"

class GasSensor : public AnalogSensor {
public:
    GasSensor(int pin, long readInterval) : AnalogSensor(pin, readInterval) {};

    void printData() override {
        Serial.print("Gas level: ");
        Serial.println(mapValue);
    }
};
