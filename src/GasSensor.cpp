#include "GasSensor.h"

GasSensor::GasSensor(int p, long rT) : pin(p), readTime(rT) {}

void GasSensor::setup() {
    lastTime = 0;
    value = 0;
}

void GasSensor::tick() {
    if (millis() - lastTime >= readTime) {
        lastTime = millis();
        value = analogRead(pin);
        printData();
    }
}

void GasSensor::printData() {
    Serial.print("Gas concentration: ");
    Serial.println(value);
}

float GasSensor::getData() {
    return value;
}
