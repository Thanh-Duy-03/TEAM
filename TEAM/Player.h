#pragma once
#include "Win.h"

class Player
{
public:
    Player();
    void LoadSprite(wstring fileName);

public:
    bool die;
    int x;
    int y;
    int currentLane;
    wstring sprite;
    short color;
    int width;
    int total;
    int level;
};