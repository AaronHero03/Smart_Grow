#include "sensors/AnalogSensor.h"

AnalogSensor::AnalogSensor(int p, long rT, int minR, int maxR) 
    : pin(p), readInterval(rT), minReading(minR), maxReading(maxR){}

void AnalogSensor::setup(){
    lastTime = 0;
    rawValue = 0;
    pinMode(pin, INPUT);
}

void AnalogSensor::calibrate(int low, int high){
    minReading = low;
    maxReading = high;
}

void AnalogSensor::tick(){
    if (millis() - lastTime >= readInterval){
        lastTime = millis();
        rawValue = readRaw(); 
        mapValue = map(rawValue, 5, 95, minReading, maxReading);
    }
}

float AnalogSensor::readRaw(){
    rawValue = analogRead(pin);
    return rawValue;
}

float AnalogSensor::getValue(){
    return mapValue;
}