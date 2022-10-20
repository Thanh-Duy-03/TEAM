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
	float timeToSpawn;
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

class Game : public ConsoleGame
{
private:
	Player player;
	Lane lane[8];
	float score;
protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fDeltaTime);
	bool SceneManager(float fDeltaTime);
	void StartMenu(float fDeltaTime);
	void StartGame(float fDeltaTime);
	void PlayGame(float fDeltaTime);
	void LoadGame(float fDeltaTime);
	void HighScoreScene(float fDeltaTime);
	void InstructionScene(float fDeltaTime);
	void UpdateLane(float fDeltaTime);
	void DrawLane();
	void DrawScore(float fDeltaTime);

private:
	int m_nCurrentState;
};
