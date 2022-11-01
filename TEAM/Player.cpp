#include "Player.h"

Player::Player()
{
    this->x = 0;
    this->y = 0;
    this->currentLane = 0;
    this->width = 0;
    this->sprite = L"";
    this->color = FG_BLACK + BG_WHITE;
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