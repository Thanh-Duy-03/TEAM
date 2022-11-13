#pragma once
#include "Win.h"
#include "Player.h"
#include "Obstacle.h"

using namespace std;

class Lane
{
private:
    int y;
    int startPos;
    int endPos;
    float time;
    float timeToChange;
    float speed;
    float distance;
    bool light;
    bool stop;
    wstring fileName;
    short bgColor;
    Obstacle prefab;
    deque<float> posList;

public:
    Lane();
    int GetY();
    int GetStart();
    int GetEnd();
    float GetTimeToChange();
    float GetSpeed();
    float GetDistance();
    bool GetLight();
    bool GetStop();
    wstring GetFileName();
    short GetBgColor();

    void SetPosY(int y);
    void SetStart(int x);
    void SetEnd(int x);
    void SetTimeToChange(float time);
    void SetSpeed(float speed);
    void SetDistance(float distance);
    void SetLight(bool light);
    void SetStop(bool stop);
    void SetFileName(wstring fileName);
    void SetBgColor(short color);

    void Update(float fDeltaTime);
    void Reset();
    void Draw(ConsoleGame *game);
    bool CheckCollider(Player *player);
};