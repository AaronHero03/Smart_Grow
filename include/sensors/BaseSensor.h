#pragma once

class BaseSensor{
public:
    virtual void setup() = 0;
    virtual void tick() = 0;
    virtual float getValue() = 0;
};