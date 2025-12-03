#pragma once
#include "actuators/Actuator.h"
#include "SensorManager.h"
#include "comunication/ThresholdsManager.h"

class ActuatorManager
{
private:
    Actuator **actuators;
    int actuatorCount;
    SensorManager &sensors;
    ThresholdManager &thresholds;

    bool updated;

public:
    ActuatorManager(Actuator **actuators, int count,
                    SensorManager &sensors,
                    ThresholdManager &thresholds);

    void setup();
    void tick();
    bool hasUpdate();
    void buildJson(JsonDocument &doc);
};
