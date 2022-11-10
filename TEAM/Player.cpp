#include "Player.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->currentLane = 0;
	this->currentIdle = 0;
	this->currentDie = 0;
	this->width = 0;
	this->bgColor = BG_BLACK;
	this->die = false;
	this->score = 0;
	this->level = 1;
}

void Player::Create()
{
	this->currentIdle = 0;
	this->currentDie = 0;
	// Idle state
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle.txt"), 0.2f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle1.txt"), 0.2f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle2.txt"), 0.2f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle1.txt"), 0.2f));
	// Die state
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie.txt"), 0.5f));
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie.txt"), 0.5f));
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie.txt"), 0.2f));
	this->width = this->idleSprites[0].first.GetWidth();
}

void Player::Set(int x, int y, int level, int score)
{
	this->x = x;
	this->y = y;
	this->currentIdle = 0;
	this->currentDie = 0;
	this->currentLane = 0;
	this->die = false;
	this->score = score;
	this->level = level;
}

bool Player::GetDie()
{
	return this->die;
}

int Player::GetCurrentLane()
{
	return this->currentLane;
}

int Player::GetScore()
{
	return this->score;
}

int Player::GetLevel()
{
	return this->level;
}

Sprite Player::GetSprite()
{
	return this->currentSprite;
}

void Player::SetLevel(int level)
{
	this->level = level;
}

void Player::SetScore(int score)
{
	this->score = score;
}

void Player::SetDie(bool die)
{
	this->die = die;
}

void Player::SetCurrentLane(int lane)
{
	this->currentLane = lane;
}

void Player::IdleState(float fDeltaTime)
{
	static float time = 0;
	this->currentSprite = this->idleSprites[this->currentIdle].first;
	if (time > this->idleSprites[this->currentIdle].second)
	{
		time = 0;
		this->currentIdle++;
		if (this->currentIdle >= this->idleSprites.size())
		{
			this->currentIdle = 0;
			return;
		}
	}
	else
	{
		time += fDeltaTime;
	}
}

bool Player::DieState(float fDeltaTime)
{
	static float time = 0;
	this->currentSprite = this->dieSprites[this->currentDie].first;
	if (time > this->dieSprites[this->currentDie].second)
	{
		time = 0;
		this->currentIdle++;
		if (this->currentIdle >= this->dieSprites.size())
		{
			this->currentDie = 0;
			return true;
		}
	}
	else
	{
		time += fDeltaTime;
	}
	return false;
}

void Player::Draw(ConsoleGame *game)
{
	game->DrawSprite((int)this->x, (int)this->y, this->currentSprite, this->bgColor);
}

// void Player::IdleState(float fDeltaTime)
// {
// 	static float time = 0;
// 	this->fgColor = FG_GREEN;
// 	if (time < 0.2f)
// 	{
// 		LoadSprite(L"Assets/Player/Player.txt");
// 	}
// 	else if (time < 0.4f)
// 	{
// 		LoadSprite(L"Assets/Player/Player1.txt");
// 	}
// 	else if (time < 0.6f)
// 	{
// 		LoadSprite(L"Assets/Player/Player2.txt");
// 	}
// 	else
// 	{
// 		time = 0;
// 	}
// 	time += fDeltaTime;
// }

// bool Player::DieState(float fDeltaTime)
// {
// 	static float time = 0;
// 	if (time < 0.5f)
// 	{
// 		this->fgColor = FG_RED;
// 		LoadSprite(L"Assets//Player/Die/firstGlow.txt");
// 	}
// 	else if (time < 1.0f)
// 	{
// 		LoadSprite(L"Assets//Player/Die/secondGlow.txt");
// 	}
// 	else if (time < 1.5f)
// 	{
// 		LoadSprite(L"Assets//Player/Die/thirdGlow.txt");
// 	}
// 	else if (time < 3.0f)
// 	{
// 		time = 0;
// 		return true; // Finish animation
// 	}
// 	time += fDeltaTime;
// 	return false;
// }