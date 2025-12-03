#include "sensors/AnalogSensor.h"
#include <iostream>

using namespace std;

AnalogSensor::AnalogSensor(String name, int p, long rT, int minR, int maxR)
    : name(name), pin(p), readInterval(rT), minReading(minR), maxReading(maxR) {}

void AnalogSensor::setup()
{
    lastTime = 0;
    rawValue = 0;
    pinMode(pin, INPUT);
}

void AnalogSensor::calibrate(int low, int high)
{
    minReading = low;
    maxReading = high;
}

void AnalogSensor::tick()
{
    if (millis() - lastTime >= readInterval)
    {
        lastTime = millis();
        rawValue = readRaw();
        mapValue = map(rawValue, 0, 4095, minReading, maxReading);
        // printData();
    }
}

float AnalogSensor::readRaw()
{
    rawValue = analogRead(pin);
    return rawValue;
}

float AnalogSensor::getValue()
{
    return mapValue;
}

String AnalogSensor::getName()
{
    return name;
}

void AnalogSensor::printData()
{
    cout << "Sensor: " << name << ": " << getValue();
}