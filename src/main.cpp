#include <Arduino.h>
#include "SensorDHT.h"

// Constrains
const int PIN_DHT = 4;
const long TIME_DHT = 5000;

// Hardware
SensorDHT dht(PIN_DHT, TIME_DHT);

void setup() {
  dht.setup();
}

void loop() {
  dht.tick();
}

