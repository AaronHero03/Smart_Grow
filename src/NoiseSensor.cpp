#include "NoiseSensor.h"

NoiseSensor::NoiseSensor(int p, long rT) : pin(p), readTime(rT) {}

void NoiseSensor::setup() {
    lastTime = 0;
    value = 0;
}

void NoiseSensor::tick() {
    if (millis() - lastTime >= readTime) {
        lastTime = millis();
        value = analogRead(pin);
        printData();
    }
}

void NoiseSensor::printData() {
    Serial.print("Noise level: ");
    Serial.println(value);
}

float NoiseSensor::getData() {
    return value;
}
