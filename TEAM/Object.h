#pragma once
#include "Win.h"
class Object
{
protected:
    float x;
    float y;
    short bgColor;
    int width;

public:
    Object();
    float GetPosX();
    float GetPosY();
    short GetBgColor();
    int GetWidth();
    void SetPosX(float x);
    void SetPosY(float y);
    void SetPos(float x, float y);
    void Move(float x, float y);
    void SetBgColor(short color);
    void SetWidth(int width);
    bool Collide(const Object &object);
};
