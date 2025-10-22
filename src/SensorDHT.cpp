#include "SensorDHT.h"

SensorDHT::SensorDHT(int p, long rT) : pin(p), readTime(rT) {};

void SensorDHT::setup(){
    temperature = 0.0;
    humidity = 0.0;
    lastTime = 0;
}

void SensorDHT::tick(){
    if(millis() - lastTime  >= readTime){
        lastTime = millis();

        TempAndHumidity data = dht.getTempAndHumidity();

        // Check for errors
        if(dht.getStatus() != DHTesp::ERROR_NONE){
            Serial.print("Error reading the sensor");
            Serial.println(dht.getStatusString());
            return;
        }

        // If there are not errors we save the data of the sensor
        temperature =  data.temperature;
        humidity = data.humidity;
        printData();    
    }
}

void SensorDHT::printData(){
    Serial.print("Temperature: ");
    Serial.print(temperature);

    Serial.print("C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

}

float SensorDHT::getHumidity(){
    return humidity;
}

float SensorDHT::getTemperature(){
    return temperature;
}