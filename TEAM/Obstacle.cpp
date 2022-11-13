#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(const Obstacle &obstacle)
{
	this->x = obstacle.x;
	this->y = obstacle.y;
	this->bgColor = obstacle.bgColor;
	this->sprite = obstacle.sprite;
}

void Obstacle::AddSprite(wstring fileName)
{
	this->sprite.Load(fileName);
	this->width = this->sprite.GetWidth();
}

Sprite Obstacle::GetSprite()
{
	return this->sprite;
}