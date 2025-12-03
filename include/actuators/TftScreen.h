#pragma once

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

class TftScreen {
public:
    // Constructor: Recibe los pines y el intervalo de actualización
    TftScreen(int cs, int dc, int rst, int sck, int mosi, long updateInterval);

    void setup(); // Método para inicializar la pantalla
    void tick();  // Método no-bloqueante que se llamará en el loop()

private:
    // Pines
    int _cs, _dc, _rst, _sck, _mosi;
    long _interval;
    long _lastTime;
    
    int _colorIndex; // Para rastrear el color a mostrar

    // Objeto de la pantalla.
    // Usamos un puntero para poder inicializarlo en setup() tras iniciar SPI.
    Adafruit_ST7789 tft;
};