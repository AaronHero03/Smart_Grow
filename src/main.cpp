#include <Arduino.h>
#include "SensorDHT.h"
#include "GasSensor.h"
#include "NoiseSensor.h"
#include "WaterSensor.h"
#include "SoilSensor.h"

// ------------------ PIN SETTINGS ------------------
const int PIN_DHT    = 4;  
const int PIN_GAS    = 34;  
const int PIN_SOIL   = 35;  
const int PIN_WATER  = 32;  
const int PIN_NOISE  = 33;  

// ------------------ READING INTERVALS ------------------
const long TIME_DHT    = 5000;
const long TIME_GAS    = 2000;
const long TIME_SOIL   = 2000;
const long TIME_WATER  = 2000;
const long TIME_NOISE  = 1000;
const long TIME_UART   = 2000;  

// ------------------ SENSORS ------------------
SensorDHT dht(PIN_DHT, TIME_DHT);
GasSensor gas(PIN_GAS, TIME_GAS);
SoilSensor soil(PIN_SOIL, TIME_SOIL);
WaterSensor water(PIN_WATER, TIME_WATER);
NoiseSensor noise(PIN_NOISE, TIME_NOISE);

// ------------------ UART CONECTION ------------------
HardwareSerial SerialToPi(2);
unsigned long lastUartSend = 0;

// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);
  SerialToPi.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);

  Serial.println("Initializing sensors...");
  dht.setup();
  gas.setup();
  soil.setup();
  water.setup();
  noise.setup();
  Serial.println("Sensors ready.\n");
}

// ------------------ MAIN LOOP ------------------
void loop() {
  dht.tick();
  gas.tick();
  soil.tick();
  water.tick();
  noise.tick();

  // ------------------ SEND DATA TO RASP ------------------
  unsigned long currentMillis = millis();
  if (currentMillis - lastUartSend >= TIME_UART) {
    lastUartSend = currentMillis;

    String data = "{";
    data += "\"temp\":" + String(dht.getTemperature()) + ",";
    data += "\"hum\":" + String(dht.getHumidity()) + ",";
    data += "\"gas\":" + String(gas.getData()) + ",";
    data += "\"soil\":" + String(soil.getData()) + ",";
    data += "\"water\":" + String(water.getData()) + ",";
    data += "\"noise\":" + String(noise.getData());
    data += "}";

    SerialToPi.println(data); // UART → Raspberry Pi
    Serial.println("UART → " + data);
  }
}
