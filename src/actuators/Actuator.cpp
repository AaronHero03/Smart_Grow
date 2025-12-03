#include "actuators/Actuator.h"

Actuator::Actuator(String n, int p, long blinkInterval)
    : name(n), pin(p), interval(blinkInterval), state(false), lastTime(0) {}

void Actuator::setup()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Actuator::activate()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void Actuator::deactivate()
{
    state = false;
    digitalWrite(pin, LOW);
}

bool Actuator::getState()
{
    return state;
}

void Actuator::blink()
{
    long now = millis();
    if (now - lastTime >= interval)
    {
        lastTime = now;
        state = !state;
        digitalWrite(pin, state ? HIGH : LOW);
    }
}

String Actuator::getName()
{
    return name;
}
