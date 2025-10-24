#pragma once
#include "Arduino.h"
#include "AnalogSensor.h"

class NoiseSensor : public AnalogSensor {
public:
    NoiseSensor(int pin, long readInterval) : AnalogSensor(pin, readInterval) {};

    void printData() override {
        Serial.print("Noise level: ");
        Serial.println(mapValue);
    }
};
