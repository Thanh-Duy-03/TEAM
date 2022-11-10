#pragma once
#include "Win.h"
#include "Object.h"

class Player : public Object
{
protected:
    bool die;
    int currentLane;
    vector<pair<Sprite, float>> idleSprites;
    int currentIdle;
    vector<pair<Sprite, float>> dieSprites;
    int currentDie;
    Sprite currentSprite;
    int score;
    int level;

public:
    Player();
    void Create();
    void Set(int x, int y, int level, int score);
    bool GetDie();
    int GetCurrentLane();
    int GetScore();
    int GetLevel();
    Sprite GetSprite();
    void SetDie(bool die);
    void SetCurrentLane(int lane);
    void SetScore(int score);
    void SetLevel(int level);
    void IdleState(float fDeltaTime);
    bool DieState(float fDeltaTime);
    void Draw(ConsoleGame *game);
    // void IdleState(float fDeltaTime);
    // bool DieState(float fDeltaTime);
};