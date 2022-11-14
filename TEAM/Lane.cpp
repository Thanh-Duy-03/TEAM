#include "Lane.h"

Lane::Lane()
{
	this->speed = 0;
	this->time = 0;
	this->distance = 0;
	this->bgColor = BG_WHITE;
	this->y = 0;
	this->stop = false;
	this->timeToChange = 3 + (rand() % 3 + 1);
	this->light = true;
}

int Lane::GetY()
{
	return this->y;
}

int Lane::GetStart()
{
	return this->startPos;
}

int Lane::GetEnd()
{
	return this->endPos;
}

float Lane::GetTimeToChange()
{
	return this->timeToChange;
}

float Lane::GetSpeed()
{
	return this->speed;
}

float Lane::GetDistance()
{
	return this->distance;
}

bool Lane::GetLight()
{
	return this->light;
}

bool Lane::GetStop()
{
	return this->stop;
}

wstring Lane::GetFileName()
{
	return this->fileName;
}

short Lane::GetBgColor()
{
	return this->bgColor;
}

void Lane::SetPosY(int y)
{
	this->y = y;
	this->prefab.SetPosY(this->y);
}

void Lane::SetStart(int x)
{
	this->startPos = x;
	this->prefab.SetPosX(this->startPos);
}

void Lane::SetEnd(int x)
{
	this->endPos = x;
}

void Lane::SetTimeToChange(float time)
{
	this->timeToChange = time;
}

void Lane::SetSpeed(float speed)
{
	this->speed = speed;
}

void Lane::SetDistance(float distance)
{
	this->distance = distance;
}

void Lane::SetLight(bool light)
{
	this->light = light;
}

void Lane::SetStop(bool stop)
{
	this->stop = stop;
}

void Lane::SetFileName(wstring fileName)
{
	this->fileName = fileName;
	this->prefab.AddSprite(this->fileName);
}

void Lane::Update(float fDeltaTime)
{

	if (this->stop)
	{
		time += fDeltaTime;
		if (this->time >= this->timeToChange)
		{
			this->time = 0;
			this->stop = false;
			this->timeToChange = (rand() % 6) + 1;
		}
		return;
	}

	if (this->time >= this->timeToChange)
	{
		this->stop = true;
		this->time = 0;
		this->timeToChange = (rand() % 6) + 1;
	}

	this->time += fDeltaTime;
	if (this->posList.empty() || abs(this->startPos - this->posList[this->posList.size() - 1]) >= this->distance)
	{
		float newPos = this->startPos;
		this->posList.push_back(newPos);
	}
	else
	{
		for (int i = 0; i < this->posList.size(); i++)
		{
			this->posList[i] += this->speed * fDeltaTime;
			if (this->posList[i] > this->endPos && this->speed >= 0)
			{
				this->posList.pop_front();
			}
			else if (this->posList[i] < this->endPos && this->speed < 0)
			{
				this->posList.pop_front();
			}
		}
	}
}

void Lane::SetBgColor(short color)
{
	this->bgColor = color;
}

void Lane::Reset()
{
	this->time = 0;
	this->timeToChange = 3 + (rand() % 3 + 1);
	this->stop = false;
	this->posList.clear();
}

void Lane::Draw(ConsoleGame* game)
{
	game->FillRectangle(0, this->y, 90, 8, L' ', this->bgColor);
	game->DrawLine(0, this->y - 1, 89, this->y - 1, PIXEL_SOLID, BG_BLACK + FG_BLACK);

	if (this->light)
	{
		for (int i = 0; i < this->posList.size(); i++)
			game->DrawSprite((int)this->posList[i], (int)this->y, this->prefab.GetSprite(), this->bgColor);
		if (this->stop)
		{
			game->Draw(5, this->y, PIXEL_SOLID, BG_RED + FG_RED);
		}
		else
		{
			game->Draw(5, this->y, PIXEL_SOLID, BG_GREEN + FG_GREEN);
		}
	}
}

bool Lane::CheckCollider(Player* player)
{
	for (int i = 0; i < this->posList.size(); i++)
	{
		this->prefab.SetPos(this->posList[i], this->y);
		if (player->Collide(this->prefab))
		{
			return true;
		}
	}
	return false;
}