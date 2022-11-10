#include "Obstacle.h"

Obstacle::Obstacle()
{
}

void Obstacle::AddSprite(wstring fileName)
{
	this->sprite.Load(fileName);
}

Sprite Obstacle::GetSprite()
{
	return this->sprite;
}