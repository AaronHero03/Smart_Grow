#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "sensors/Sensor.h"
#include "sensors/SensorDHT.h"

class SensorManager
{
private:
    Sensor **sensors;
    int sensorCount;

public:
    SensorManager(Sensor **sensors, int count);

    void setup();
    void tick();
    void buildJson(JsonDocument &doc);

    Sensor *getSensor(const String &name);
    float getSensorValue(const String &name);
};
