#pragma once

#include <ArduinoJson.h>

struct Thresholds
{
    float soil_min = 30;
    float temp_max = 28;
    float humidity_min = 30;
    float water_min = 30;
};

class ThresholdManager
{
private:
    Thresholds t;

public:
    Thresholds get() { return t; }

    void applyJson(JsonDocument &doc);
    void toJson(JsonDocument &doc);
};
