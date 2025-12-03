#include "comunication/ThresholdsManager.h"

void ThresholdManager::applyJson(JsonDocument &doc)
{
    if (doc.containsKey("soil_min"))
        t.soil_min = doc["soil_min"];
    if (doc.containsKey("temp_max"))
        t.temp_max = doc["temp_max"];
    if (doc.containsKey("humidity_min"))
        t.humidity_min = doc["humidity_min"];
    if (doc.containsKey("water_min"))
        t.water_min = doc["water_min"];
}

void ThresholdManager::toJson(JsonDocument &doc)
{
    doc["ack"] = "thresholds_updated";
    doc["soil_min"] = t.soil_min;
    doc["temp_max"] = t.temp_max;
    doc["humidity_min"] = t.humidity_min;
    doc["water_min"] = t.water_min;
}
