#include "comunication/UartController.h"

UartController::UartController(int uartNum, long baud, int rx, int tx,
                               SensorManager &sm, ActuatorManager &am, ThresholdManager &th,
                               long interval)
    : transmitter(uartNum, baud, rx, tx),
      sensors(sm),
      actuators(am),
      thresholds(th),
      interval(interval) {}

void UartController::setup()
{
    transmitter.setup();
}

void UartController::tick()
{
    unsigned long now = millis();

    if (now - lastSend >= interval)
    {
        lastSend = now;

        StaticJsonDocument<256> d;
        sensors.buildJson(d);

        transmitter.send(d);
    }

    if (actuators.hasUpdate())
    {
        StaticJsonDocument<128> d;
        actuators.buildJson(d);
        transmitter.send(d);
    }

    StaticJsonDocument<256> incoming;
    if (transmitter.receive(incoming))
    {
        thresholds.applyJson(incoming);

        StaticJsonDocument<128> ack;
        thresholds.toJson(ack);

        transmitter.send(ack);
    }
}
