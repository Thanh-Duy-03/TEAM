#include "Lane.h"

Lane::Lane()
{
    this->speed = 0;
    this->sprite = L"";
    this->time = 0;
    this->distance = 0;
    this->color = FG_BLACK + BG_WHITE;
    this->y = 0;
    this->stop = false;
    this->timeToChange = 3 + (rand() % 3 + 1);
}

void Lane::LoadSprite(wstring fileName)
{
    wfstream file(fileName);
    this->sprite = L"";
    this->sprite = L"";
    if (file.is_open())
    {
        locale loc(locale(), new codecvt_utf8<wchar_t>);
        file.imbue(loc);
        wstring line;
        int maxWidth = 0;
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
void Lane::Update(float fDeltaTime, int screenWidth)
{

    if (this->stop)
    {
        time += fDeltaTime;
        if (this->time >= this->timeToChange)
        {
            this->time = 0;
            this->stop = false;
            this->timeToChange = 3 + (rand() % 3 + 1);
        }
        return;
    }

    if (this->time >= this->timeToChange)
    {
        this->stop = true;
        // ran = 9 * (rand() % 6 + 1);
        this->time = 0;
        this->timeToChange = 3 + (rand() % 3 + 1);
    }

    this->time += fDeltaTime;
    if (this->posList.empty() || abs(this->x - this->posList[this->posList.size() - 1]) >= this->distance)
    {
        float newPos = this->x;
        this->posList.push_back(newPos);
        this->time = 0;
    }
    else
    {
        for (int i = 0; i < this->posList.size(); i++)
        {
            this->posList[i] += this->speed * fDeltaTime;
            if (this->posList[i] >= screenWidth || this->posList[i] < -50)
            {
                this->posList.pop_front();
            }
        }
    }
}

void Lane::Reset()
{
    this->time = 0;
    this->timeToChange = 3 + (rand() % 3 + 1);
    this->stop = false;
    this->posList.clear();
}

void Lane::Draw(ConsoleGame *game)
{
    for (int i = 0; i < this->posList.size(); i++)
        game->DrawStringAlpha((int)this->posList[i], (int)this->y, this->sprite, this->color);
}