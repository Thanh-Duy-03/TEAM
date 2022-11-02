#pragma once
#include "Win.h"
#include "Player.h"
#include "Lane.h"
#include "Save.h"

using namespace std;

class Game : public ConsoleGame
{
private:
	Player player;
	Lane lane[8];
	float score;
	Save High_Score[10];
	deque<Save> Load_Game;

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
	void DrawLanes();
	void DrawScore(float fDeltaTime);
	void SaveGame(float fDeltaTime);
	void DieGame(float fDeltaTime);
	void effect(float time);

private:
	int m_nCurrentState;
};
