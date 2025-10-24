#pragma once

#include "Arduino.h"
#include "DHTesp.h"
#include "BaseSensor.h"

class SensorDHT : public Sensor{
protected:
    DHTesp dht;
    
    int pin;
    
    float temperature;
    float humidity;

    unsigned long lastTime;
    long readTime;

public:
    SensorDHT(int p, long rT);

    void setup();
    void tick();
    void printData();
    
    float getHumidity();
    float getTemperature();
    float getValue() override;
};