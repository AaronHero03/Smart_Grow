#pragma once

#include <HardwareSerial.h>
#include <ArduinoJson.h>

class UartTransmitter
{
private:
    HardwareSerial serial;

    long baud;
    int rxPin;
    int txPin;

public:
    UartTransmitter(int uartNum, long baud, int rx, int tx);

    void setup();
    void send(JsonDocument &doc);
    bool receive(JsonDocument &doc);
};
