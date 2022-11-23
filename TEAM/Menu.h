#pragma once
#include "Win.h"
#include "Player.h"
#include "Lane.h"
#include "Save.h"
#include "Alphabet.h"
#include "Object.h"
#include "Obstacle.h"

using namespace std;

class Game : public ConsoleGame
{
private:
	Player player;
	Lane lane[8];
	float score;
	deque<Save> highScores;
	deque<Save> loadGames;
	AudioSample musicMenu;
	AudioSample musicGame;
	AudioSample musicWin;
	AudioSample musicLose;
	int masterAudio;
	int musicAudio;
	int sfxAudio;
	int m_nCurrentState;

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
	void Setting(float fDeltaTime);
	void UpdateLane(float fDeltaTime);
	void DrawLanes();
	void DrawScore1(float fDeltaTime);
	void DrawScore2(float fDeltaTime);
	void DrawLoadGame(float fDeltaTime, int Vt);
	void DrawHighScore(float fDeltaTime);
	void DrawSetting(float fDeltaTime, int Vt);
	void SaveGame(float fDeltaTime);
	void DieGameTrc(float fDeltaTime);
	void DieGameSau(float fDeltaTime);
	void SaveData(string fileName, deque<Save> saves);
	void LoadData(string fileName, deque<Save> &saves);
	void endEffect(float fDeltaTime);
	void winEffect(float fDeltaTime);
	void LoadAudioSetting(string name);
	void SaveAudioSetting(string name);
};
