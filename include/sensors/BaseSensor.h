#pragma once

class Sensor{
public:
    virtual void setup() = 0;
    virtual void tick() = 0;
    virtual float getValue() = 0;
};