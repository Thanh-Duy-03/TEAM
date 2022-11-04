#pragma once
#include "Win.h"

using namespace std;

class Lane
{
public:
    Lane();
    void LoadSprite(wstring fileName);
    void Update(float fDeltaTime, int screenWidth);
    void Reset();
    void Draw(ConsoleGame *game);

public:
    int distance;
    float time;
    float speed;
    float timeToChange;
    int y;
    int x;
    bool stop;
    wstring sprite;
    short color;
    short fgColor;
    short bgColor;
    int width;
    deque<float> posList;
};