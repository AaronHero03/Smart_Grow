#pragma once
#include <TFT_eSPI.h>

enum FaceType
{
    FACE_HAPPY,
    FACE_SLEEPY,
    FACE_CONFUSED,
    FACE_ANGRY,
    FACE_SAD
};

class TftFace
{
public:
    TftFace();
    void init();
    void show(FaceType type);

private:
    TFT_eSPI tft;
    int w, h;

    void clearFace();
    void drawHappy();
    void drawSleepy();
    void drawConfused();
    void drawAngry();
    void drawSad();
};
