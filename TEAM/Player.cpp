#include "Player.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->currentLane = 0;
	this->width = 0;
	this->sprite = L"";
	this->fgColor = FG_BLACK;
	this->bgColor = BG_WHITE;
	this->die = false;
	this->total = 0;
	this->level = 1;
}

void Player::LoadSprite(wstring fileName)
{
	wfstream file(fileName);
	this->sprite = L"";
	if (file.is_open())
	{
		locale loc(locale(), new codecvt_utf8_utf16<wchar_t>);
		file.imbue(loc);
		int maxWidth = 0;
		wstring line;
		while (!file.eof())
		{
			getline(file, line);
			if (maxWidth < line.size())
				maxWidth = line.size();
			this->sprite += line + L"\n";
		}
		this->width = maxWidth;
	}
	file.close();
}

void Player::IdleState(float fDeltaTime)
{
	static float time = 0;
	this->fgColor = FG_GREEN;
	if (time < 0.2f)
	{
		LoadSprite(L"Assets/Player/Player.txt");
	}
	else if (time < 0.4f)
	{
		LoadSprite(L"Assets/Player/Player1.txt");
	}
	else if (time < 0.6f)
	{
		LoadSprite(L"Assets/Player/Player2.txt");
	}
	else
	{
		time = 0;
	}
	time += fDeltaTime;
}

bool Player::DieState(float fDeltaTime)
{
	static float time = 0;
	if (time < 0.5f)
	{
		this->fgColor = FG_RED;
		LoadSprite(L"Assets//Player/Die/firstGlow.txt");
	}
	else if (time < 1.0f)
	{
		LoadSprite(L"Assets//Player/Die/secondGlow.txt");
	}
	else if (time < 1.5f)
	{
		LoadSprite(L"Assets//Player/Die/thirdGlow.txt");
	}
	else if (time < 3.0f)
	{
		time = 0;
		return true; // Finish animation
	}
	time += fDeltaTime;
	return false;
}