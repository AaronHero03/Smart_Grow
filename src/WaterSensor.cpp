#include "WaterSensor.h"

WaterSensor::WaterSensor(int p, long rT) : pin(p), readTime(rT) {};

void WaterSensor::setup(){
    lastTime = 0;
    value = 0;
}

void WaterSensor::tick(){
    if(millis() - lastTime  >= readTime){
        lastTime = millis();

        value = analogRead(pin);
        printData();    
    }
}

void WaterSensor::printData(){
    Serial.print("Water level: ");
    Serial.println(value);
}

float WaterSensor::getData(){
    return value;
}