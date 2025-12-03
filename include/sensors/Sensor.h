#pragma once
#include <string>

using namespace std;

class Sensor
{
public:
    virtual void setup() = 0;
    virtual void tick() = 0;
    virtual float getValue() = 0;
    virtual String getName() = 0;
};