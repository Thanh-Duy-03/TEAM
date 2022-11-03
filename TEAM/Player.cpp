#include "Player.h"

Player::Player()
{
    this->x = 0;
    this->y = 0;
    this->currentLane = 0;
    this->width = 0;
    this->sprite = L"";
    this->color = FG_BLACK + BG_WHITE;
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
        locale loc(locale(), new codecvt_utf8<wchar_t>);
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
    LoadSprite(L"Player.txt");
}

bool Player::DieState(float fDeltaTime)
{
    static float time = 0;
    if (time < 0.5f)
    {
        this->color = FG_RED + BG_WHITE;
        LoadSprite(L"firstGlow.txt");
    }
    else if (time < 1.0f)
    {
        LoadSprite(L"secondGlow.txt");
    }
    else if (time < 1.5f)
    {
        LoadSprite(L"thirdGlow");
    }
    else if (time < 3.0f)
    {
        time == 0;
        return true; // Finish animation
    }
    time += fDeltaTime;
    return false;
}