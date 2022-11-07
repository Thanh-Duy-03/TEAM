#pragma once
#include "Win.h"

class Player
{
public:
    Player();
    void LoadSprite(wstring fileName);
    void IdleState(float fDeltaTime);
    bool DieState(float fDeltaTime);

public:
    bool die;
    float x;
    int y;
    int currentLane;
    wstring sprite;
    short fgColor;
    short bgColor;
    int width;
    int total;
    int level;
};