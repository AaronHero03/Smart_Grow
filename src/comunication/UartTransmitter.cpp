#include "comunication/UartTransmitter.h"

UartTransmitter::UartTransmitter(int uartNum, long baud, int rx, int tx)
    : serial(uartNum), baud(baud), rxPin(rx), txPin(tx) {}

void UartTransmitter::setup()
{
    serial.begin(baud, SERIAL_8N1, rxPin, txPin);
}

void UartTransmitter::send(JsonDocument &doc)
{
    String out;
    serializeJson(doc, out);
    serial.println(out);
}

bool UartTransmitter::receive(JsonDocument &doc)
{
    if (!serial.available())
        return false;

    String line = serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0)
        return false;

    auto err = deserializeJson(doc, line);
    return !err;
}
