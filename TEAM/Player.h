#pragma once
#include "Win.h"
#include "Object.h"

class Player : public Object
{
protected:
    bool die;
    bool pause;
    int currentLane;
    vector<pair<Sprite, float>> idleSprites;
    int currentIdle;
    vector<pair<Sprite, float>> dieSprites;
    int currentDie;
    int score;
    int level;
    AudioSample sound;
    AudioSample moveSound;

public:
    Player();
    void Create();
    void Set(int x, int y, int level, int score);
    bool GetDie();
    bool GetPause();
    int GetCurrentLane();
    int GetScore();
    int GetLevel();
    void SetDie(bool die);
    void SetPause(bool pause);
    void SetCurrentLane(int lane);
    void SetScore(int score);
    void SetLevel(int level);
    void SetMove(wstring link);
    void playMove();
    void IdleState(float fDeltaTime);
    bool DieState(float fDeltaTime);
    void Draw(ConsoleGame *game);
    void SetVolume(int volume);
};