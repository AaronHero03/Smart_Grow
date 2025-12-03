#include "SensorManager.h"

SensorManager::SensorManager(Sensor **sensors, int count)
    : sensors(sensors), sensorCount(count) {}

void SensorManager::setup()
{
    for (int i = 0; i < sensorCount; i++)
        sensors[i]->setup();
}

void SensorManager::tick()
{
    for (int i = 0; i < sensorCount; i++)
        sensors[i]->tick();
}

void SensorManager::buildJson(JsonDocument &doc)
{
    for (int i = 0; i < sensorCount; i++)
    {
        String name = sensors[i]->getName();

        if (name == "dht")
        {
            auto *dht = (SensorDHT *)sensors[i];
            doc["temperature"] = dht->getTemperature();
            doc["humidity"] = dht->getHumidity();
        }
        else
        {
            doc[name] = sensors[i]->getValue();
        }
    }
}

Sensor *SensorManager::getSensor(const String &name)
{
    for (int i = 0; i < sensorCount; i++)
    {
        if (sensors[i]->getName() == name)
            return sensors[i];
    }
    return nullptr;
}

float SensorManager::getSensorValue(const String &name)
{
    Sensor *s = getSensor(name);
    if (!s)
        return 0;

    if (name == "dht")
        return 0;
    return s->getValue();
}
