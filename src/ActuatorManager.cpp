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
            if (soil < t.soil_min)
            {
                if (water > t.water_min)
                {
                    Serial.println("Bomba prendida");
                    actuators[i]->activate();
                }
                else
                {
                    Serial.println("Bomba apagada");
                    actuators[i]->deactivate();
                }
            }
            else
            {
                actuators[i]->deactivate();
            }
            // Serial.println("Bomba apagada");
        }

        if (name == "fan")
        {
            if (temp > t.temp_max || hum < t.humidity_min)
            {
                actuators[i]->activate();
            }
            else
            {
                // Serial.println("Ventilador apagado");
                actuators[i]->deactivate();
            }
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
