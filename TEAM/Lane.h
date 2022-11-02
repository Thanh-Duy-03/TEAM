#pragma once
#include "Win.h"

using namespace std;

class Lane
{
public:
    Lane();
    void LoadSprite(wstring fileName);
    void Update(float fDeltaTime, int screenWidth);

public:
    int Kc;
    float time;
    float speed;
    float timeToStop;
    float timeStop;
    int y;
    int x;
    bool stop;
    wstring sprite;
    short color;
    int width;
    deque<float> posList;
};