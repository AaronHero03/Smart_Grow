#pragma once

#include "Arduino.h"
#include "DHTesp.h"
#include "Sensor.h"

class SensorDHT : public Sensor
{
protected:
    DHTesp dht;

    String name;

    int pin;
    long lastTime;
    long readTime;

    float temperature;
    float humidity;

public:
    SensorDHT(int p, long rT);

    void setup() override;
    void tick() override;

    float getHumidity();
    float getTemperature();

    float getValue() override;
    String getName() override { return "dht"; };
};