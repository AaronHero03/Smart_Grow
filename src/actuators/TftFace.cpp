#include "actuators/TftFace.h"

TftFace::TftFace() : tft(TFT_eSPI()) {}

void TftFace::init()
{
    tft.init();
    tft.setRotation(1);
    w = tft.width();
    h = tft.height();

    tft.fillScreen(TFT_BLACK);
}

void TftFace::clearFace()
{
    tft.fillScreen(TFT_WHITE);
}

void TftFace::show(FaceType type)
{
    clearFace();
    switch (type)
    {
    case FACE_HAPPY:
        drawHappy();
        break;
    case FACE_SLEEPY:
        drawSleepy();
        break;
    case FACE_CONFUSED:
        drawConfused();
        break;
    case FACE_ANGRY:
        drawAngry();
        break;
    case FACE_SAD:
        drawSad();
        break;
    }
}

/* =====================
   DIBUJOS PIXEL-ART
   ===================== */

void TftFace::drawHappy()
{
    tft.fillCircle(w / 2 - 40, h / 2 - 30, 8, TFT_CYAN);
    tft.fillCircle(w / 2 + 40, h / 2 - 30, 8, TFT_CYAN);
    tft.fillRoundRect(w / 2 - 20, h / 2 + 10, 40, 10, 3, TFT_CYAN);
}

void TftFace::drawSleepy()
{
    // Color del fondo (aprox. #0C1735)
    uint16_t bg = tft.color565(0x0C, 0x17, 0x35);
    tft.fillScreen(TFT_RED);
}

void TftFace::drawConfused()
{
    tft.drawRect(w / 2 - 45, h / 2 - 40, 20, 20, TFT_CYAN);
    tft.drawRect(w / 2 + 25, h / 2 - 40, 20, 20, TFT_CYAN);
    tft.fillCircle(w / 2, h / 2 + 20, 10, TFT_CYAN);
}

void TftFace::drawAngry()
{
    tft.fillTriangle(w / 2 - 50, h / 2 - 40, w / 2 - 35, h / 2 - 20, w / 2 - 20, h / 2 - 40, TFT_RED);
    tft.fillTriangle(w / 2 + 20, h / 2 - 40, w / 2 + 35, h / 2 - 20, w / 2 + 50, h / 2 - 40, TFT_RED);
    tft.drawLine(w / 2 - 25, h / 2 + 30, w / 2 + 25, h / 2 + 30, TFT_RED);
}

void TftFace::drawSad()
{
    tft.fillCircle(w / 2 - 40, h / 2 - 30, 8, TFT_CYAN);
    tft.fillCircle(w / 2 + 40, h / 2 - 30, 8, TFT_CYAN);

    tft.fillRect(w / 2 - 10, h / 2 - 10, 10, 40, TFT_CYAN);
    tft.fillRect(w / 2 + 0, h / 2 - 10, 10, 40, TFT_CYAN);

    tft.fillRoundRect(w / 2 - 20, h / 2 + 15, 40, 10, 3, TFT_CYAN);
}
