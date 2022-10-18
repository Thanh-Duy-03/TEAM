﻿#pragma once
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
	int y;
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

protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fDeltaTime);
	bool SceneManager(float fDeltaTime);
	void StartMenu(float fDeltaTime);
	void StartGame(float fDeltaTime, int level);
	void PlayGame(float fDeltaTime);
	void LoadGame(float fDeltaTime);
	void HighScoreScene(float fDeltaTime);
	void InstructionScene(float fDeltaTime);
	void UpdateLane(float fDeltaTime);
	void DrawLane();

private:
	int m_nCurrentState;
};
