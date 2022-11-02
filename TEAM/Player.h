#pragma once
#include "Win.h"

class Player
{
public:
    Player();
    void LoadSprite(wstring fileName);
    void IdleState(float fDeltaTime);
    float DieState(float fDeltaTime);

public:
    bool die;
    int x;
    int y;
    int currentLane;
    wstring sprite;
    short color;
    short fgColor;
    short bgColor;
    int width;
    int total;
    int level;
};