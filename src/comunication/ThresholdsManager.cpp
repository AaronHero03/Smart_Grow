#include "comunication/ThresholdsManager.h"

void ThresholdManager::applyJson(JsonDocument &doc)
{
    if (!doc.containsKey("thresholds"))
        return;

    JsonObject th = doc["thresholds"];

    if (th.containsKey("soil_min"))
        t.soil_min = th["soil_min"];

    if (th.containsKey("temp_max"))
        t.temp_max = th["temp_max"];

    if (th.containsKey("humidity_min"))
        t.humidity_min = th["humidity_min"];
}

void ThresholdManager::toJson(JsonDocument &doc)
{
    doc["ack"] = "thresholds_updated";
    doc["soil_min"] = t.soil_min;
    doc["temp_max"] = t.temp_max;
    doc["humidity_min"] = t.humidity_min;
    doc["water_min"] = t.water_min;
}
