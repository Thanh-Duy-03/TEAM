#pragma once
#include "Object.h"
class Obstacle : public Object
{
protected:
    Sprite sprite;

public:
    Obstacle();
    void AddSprite(wstring fileName);
    Sprite GetSprite();
};
