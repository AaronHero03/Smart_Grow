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

    Serial.print("[UART - TX -> PC] Sent: ");
    Serial.println(out);
}

bool UartTransmitter::receive(JsonDocument &doc)
{
    if (!serial.available())
        return false;

    String line = serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0)
        return false;

    Serial.print("[UART - RX <- PC] Raw: ");
    Serial.println(line);

    auto err = deserializeJson(doc, line);
    if (err)
    {
        Serial.println("[UART] JSON parse ERROR");
        return false;
    }

    Serial.println("[UART] JSON parsed OK");
    return true;
}
