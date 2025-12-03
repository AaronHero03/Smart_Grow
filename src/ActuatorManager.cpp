#include "ActuatorManager.h"
#include "sensors/SensorDHT.h"

ActuatorManager::ActuatorManager(Actuator **actuators, int count,
                                 SensorManager &sensors,
                                 ThresholdManager &thresholds)
    : actuators(actuators), actuatorCount(count), sensors(sensors), thresholds(thresholds), updated(false) {}

void ActuatorManager::setup()
{
    for (int i = 0; i < actuatorCount; i++)
        actuators[i]->setup();
}

void ActuatorManager::tick()
{
    updated = false;

    Thresholds t = thresholds.get();

    float soil = sensors.getSensorValue("soil");
    float water = sensors.getSensorValue("water");

    SensorDHT *dht = (SensorDHT *)sensors.getSensor("dht");
    float temp = dht->getTemperature();
    float hum = dht->getHumidity();

    for (int i = 0; i < actuatorCount; i++)
    {
        bool prevState = actuators[i]->getState();
        String name = actuators[i]->getName();

        if (name == "pump")
        {
            if (soil < t.soil_min || water < t.water_min)
                actuators[i]->activate();
            else
                actuators[i]->deactivate();
        }

        if (name == "fan")
        {
            if (temp > t.temp_max || hum < t.humidity_min)
                actuators[i]->activate();
            else
                actuators[i]->deactivate();
        }

        if (actuators[i]->getState() != prevState)
            updated = true;
    }
}

bool ActuatorManager::hasUpdate()
{
    return updated;
}

void ActuatorManager::buildJson(JsonDocument &doc)
{
    for (int i = 0; i < actuatorCount; i++)
    {
        JsonObject note = doc.createNestedObject("notification");
        note["actuator"] = actuators[i]->getName();
        note["state"] = actuators[i]->getState();
    }
}
