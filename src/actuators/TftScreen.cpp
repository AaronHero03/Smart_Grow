#include "actuators/TftScreen.h"

// Constructor: Inicializa la lista de miembros
TftScreen::TftScreen(int cs, int dc, int rst, int sck, int mosi, long updateInterval)
    : _cs(cs), _dc(dc), _rst(rst), _sck(sck), _mosi(mosi), _interval(updateInterval),
      tft(Adafruit_ST7789(cs, dc, rst)) { // <-- Inicializa el objeto tft aquí
    
    _lastTime = 0;
    _colorIndex = 0;
}

void TftScreen::setup() {
    Serial.println("Iniciando pantalla TFT ST7789...");

    // Inicializar SPI manualmente (usando los pines miembro)
    SPI.begin(_sck, -1, _mosi, _cs);
    
    // Inicializar la pantalla
    tft.init(240, 320);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);

    // Mensaje de bienvenida
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.setCursor(10, 30);
    tft.println("Hola Angeles!");
    tft.setTextColor(ST77XX_YELLOW);
    tft.println("ESP32 + TFT OK");
    
    _lastTime = millis(); // Empezamos el temporizador
}

// Este es el reemplazo no-bloqueante de tu loop()
void TftScreen::tick() {
    unsigned long currentTime = millis();

    // Comprueba si ha pasado el intervalo (ej. 1 segundo)
    if (currentTime - _lastTime >= _interval) {
        _lastTime = currentTime; // Resetea el temporizador

        // Cambia el color de fondo según el índice
        switch (_colorIndex) {
            case 0:
                tft.fillScreen(ST77XX_RED);
                break;
            case 1:
                tft.fillScreen(ST77XX_BLUE);
                break;
            case 2:
                tft.fillScreen(ST77XX_GREEN);
                break;
        }
        
        _colorIndex++; // Avanza al siguiente color
        if (_colorIndex > 2) {
            _colorIndex = 0; // Vuelve al inicio
        }
    }
}