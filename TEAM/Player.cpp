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
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle.txt"), 0.1f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle1.txt"), 0.1f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle2.txt"), 0.1f));
	this->idleSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Idle/PlayerIdle1.txt"), 0.1f));
	// Die state
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie1.txt"), 0.5f));
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie2.txt"), 0.5f));
	this->dieSprites.push_back(pair<Sprite, float>(Sprite(L"Assets/Player/Die/PlayerDie3.txt"), 0.2f));
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
	if (time >= this->dieSprites[this->currentDie].second)
	{
		time = 0;
		this->currentDie++;
		if (this->currentDie >= this->dieSprites.size())
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

void Player::Draw(ConsoleGame* game)
{
	if (this->die)
		game->DrawSprite((int)this->x, (int)this->y, this->dieSprites[this->currentDie].first, this->bgColor);
	else
		game->DrawSprite((int)this->x, (int)this->y, this->idleSprites[this->currentIdle].first, this->bgColor);
}