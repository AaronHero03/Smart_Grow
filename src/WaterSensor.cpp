#include "WaterSensor.h"

WaterSensor::WaterSensor(int p, long rT) : pin(p), readTime(rT) {};

void WaterSensor::setup(){
    lastTime = 0;
    value = 0;
}

void WaterSensor::tick(){
    if(millis() - lastTime  >= readTime){
        lastTime = millis();
        int raw = analogRead(pin);
        value = map(raw, 1023, 0, 0, 100); 
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