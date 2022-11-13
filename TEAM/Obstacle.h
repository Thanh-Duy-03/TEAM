#pragma once
#include "Object.h"
class Obstacle : public Object
{
protected:
    Sprite sprite;

public:
    Obstacle();
    Obstacle(const Obstacle &obstacle);
    void AddSprite(wstring fileName);
    Sprite GetSprite();
};
