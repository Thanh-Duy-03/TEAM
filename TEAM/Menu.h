#pragma once
#include <iostream>
#include "Win.h"

using namespace std;

class Player
{
public:
	Player();
	void UpdatePos(int x, int y, int lane);
	int CurrentLane();
	int X();
	int Y();
	int Width();

public:
	bool die;

private:
	int x;
	int y;
	int currentLane;
	wstring sprite;
	int width;
};

class Game : public ConsoleGame
{
private:
	// class xử lí game:
	// 
public:
protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fDeltaTime);
	bool SceneManager(float fDeltaTime);
	void StartMenu(float fDeltaTime);
	void PlayGame(float fDeltaTime);
	void LoadGame(float fDeltaTime);
	void HighScoreScene(float fDeltaTime);
	void InstructionScene(float fDeltaTime);

private:
	int m_nCurrentState;
};

