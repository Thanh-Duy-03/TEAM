#pragma once
#include "Win.h"
#include <deque>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <random>

using namespace std;

class Player
{
public:
	Player();
	void LoadSprite(wstring fileName);

public:
	bool die;
	int x;
	int y;
	int currentLane;
	wstring sprite;
	short color;
	int width;
	int total;
	int level;
};

class Lane
{
public:
	Lane();
	void LoadSprite(wstring fileName);
	void Update(float fDeltaTime, int screenWidth);

public:
	int Kc;
	float time;
	float speed;
	float timeToStop;
	float timeStop;
	int y;
	bool stop;
	wstring sprite;
	short color;
	int width;
	deque<float> posList;
};

class Save
{
public:
	wstring name;
	int level;
	int point;
	Save()
	{
		name = L"";
		level = 0;
		point = 0;
	}
};

class Game : public ConsoleGame
{
private:
	Player player;
	Lane lane[8];
	float score;
	Save Load_Game[10], High_Score[10];

protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fDeltaTime);
	bool SceneManager(float fDeltaTime);
	void StartMenu(float fDeltaTime);
	void StartGame(float fDeltaTime, int level, int score);
	void PlayGame(float fDeltaTime);
	void LoadGame(float fDeltaTime);
	void HighScoreScene(float fDeltaTime);
	void InstructionScene(float fDeltaTime);
	void UpdateLane(float fDeltaTime);
	void DrawLane();
	void DrawScore(float fDeltaTime);
	void SaveGame(float fDeltaTime);
	void DieGame(float fDeltaTime);
	void effect(float time);

private:
	int m_nCurrentState;
};
