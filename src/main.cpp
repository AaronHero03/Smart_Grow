#include <Arduino.h>
#include "sensors/GasSensor.h"
#include "sensors/NoiseSensor.h"
#include "sensors/SoilSensor.h"
#include "sensors/SensorDHT.h"
#include "sensors/WaterSensor.h"

// DHT, GAS, SOIL, WATER, NOISE
const int SENSOR_COUNT = 5;

// ------------------ PIN SETTINGS ------------------
const int PINS[SENSOR_COUNT] = {4, 34, 35, 32, 33};

// ------------------ READING INTERVALS ------------------
const long TIMES[SENSOR_COUNT + 1] = {3000, 2000, 2000, 2000, 1000, 2000};

// ------------------ SENSORS ------------------
SensorDHT   dht(PINS[0],    TIMES[0]);
GasSensor   gas(PINS[1],    TIMES[1]);
SoilSensor  soil(PINS[2],   TIMES[2]);
WaterSensor water(PINS[3],  TIMES[3]);
NoiseSensor noise(PINS[4],  TIMES[4]);

Sensor* sensors[SENSOR_COUNT] = {&dht,&gas,&soil,&water,&noise};

// ------------------ UART SETUP ------------------

HardwareSerial SerialToPi(2);
unsigned long lastUartSend = 0;

// ------------------ AUX FUNCTIONS ------------------
void sendUARTData(){
  unsigned long currentMillis = millis();
  if (currentMillis - lastUartSend >= TIMES[5]) {
    lastUartSend = currentMillis;
    
    String data = "{";
    data += "\"temp\":" + String(dht.getTemperature()) + ",";
    data += "\"hum\":" + String(dht.getHumidity()) + ",";
    data += "\"gas\":" + String(gas.getValue()) + ",";
    data += "\"soil\":" + String(soil.getValue()) + ",";
    data += "\"water\":" + String(water.getValue()) + ",";
    data += "\"noise\":" + String(noise.getValue());
    data += "}";
    
    SerialToPi.println(data); // UART → Raspberry Pi
  }
}

void setup() {
  Serial.begin(115200);
  SerialToPi.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);

  for(auto s : sensors){
    s->setup();
  }
}

void loop() {
  for(auto s : sensors){
    s->tick();
  }
  sendUARTData();
}