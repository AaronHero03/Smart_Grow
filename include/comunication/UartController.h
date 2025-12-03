#pragma once

#include "comunication/UartTransmitter.h"
#include "../SensorManager.h"
#include "../ActuatorManager.h"
#include "ThresholdsManager.h"

class UartController
{
private:
    UartTransmitter transmitter;
    SensorManager &sensors;
    ActuatorManager &actuators;
    ThresholdManager &thresholds;

    long interval;
    unsigned long lastSend = 0;

public:
    UartController(int uartNum, long baud, int rx, int tx, SensorManager &sm, ActuatorManager &am, ThresholdManager &th, long interval);

    void setup();
    void tick();
};
