#include "SoilSensor.h"

SoilSensor::SoilSensor(int p, long rT) : pin(p), readTime(rT) {}

void SoilSensor::setup() {
    lastTime = 0;
    value = 0;
}

void SoilSensor::tick() {
    if (millis() - lastTime >= readTime) {
        lastTime = millis();
        int raw = analogRead(pin);
        value = map(raw, 1023, 0, 0, 100); 
        printData();
    }
}

void SoilSensor::printData() {
    Serial.print("Soil humidity: ");
    Serial.print(value);
    Serial.println("%");
}

float SoilSensor::getData() {
    return value;
}
