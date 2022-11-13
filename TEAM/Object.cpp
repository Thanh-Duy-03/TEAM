#include "Object.h"
Object::Object()
{
    this->x = 0;
    this->y = 0;
    this->bgColor = 0;
    this->width = 0;
}

float Object::GetPosX()
{
    return this->x;
}

float Object::GetPosY()
{
    return this->y;
}

short Object::GetBgColor()
{
    return this->bgColor;
}

int Object::GetWidth()
{
    return this->width;
}

void Object::SetPosX(float x)
{
    this->x = x;
}

void Object::SetPosY(float y)
{
    this->y = y;
}

void Object::SetPos(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Object::Move(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Object::SetBgColor(short color)
{
    if (color % 16 != 0)
    {
        color -= color % 16;
    }
    this->bgColor = color;
}

void Object::SetWidth(int width)
{
    this->width = width;
}

bool Object::Collide(const Object &object)
{
    return (this->x + this->width >= object.x) && (this->x <= object.x + object.width);
}