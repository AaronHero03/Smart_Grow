#include <Arduino.h>
#include "SensorManager.h"
#include "ActuatorManager.h"
#include "comunication/UartController.h"
#include "sensors/AnalogSensor.h"
#include "sensors/SensorDHT.h"
#include "actuators/Actuator.h"

#define UART_NUM 2
#define UART_RX 16
#define UART_TX 17
#define UART_BAUD 9600

#define SEND_INTERVAL 5000

const int FAN_PIN = 26;
const int PUMP_PIN = 25;

#define SOIL_PIN 34
#define WATER_PIN 35
#define DHT_PIN 27

Sensor *sensorList[] = {
    new AnalogSensor("soil", SOIL_PIN, 1000),
    new AnalogSensor("water", WATER_PIN, 1000),
    new SensorDHT(DHT_PIN, 2000)};

Actuator *actuators[] = {
    new Actuator("fan", FAN_PIN, 5000),
    new Actuator("pump", PUMP_PIN, 2500)};

SensorManager sensorManager(sensorList, 3);
ThresholdManager thresholds;
ActuatorManager actuatorManager(actuators, 2, sensorManager, thresholds);

UartController uartController(
    UART_NUM,
    UART_BAUD,
    UART_RX,
    UART_TX,
    sensorManager,
    actuatorManager,
    thresholds,
    SEND_INTERVAL);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n=== ESP32 STARTED ===");

    sensorManager.setup();
    uartController.setup();

    Serial.println("System ready.");
}

void loop()
{
    sensorManager.tick();
    actuatorManager.tick();
    uartController.tick();
}
