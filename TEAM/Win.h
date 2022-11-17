#pragma once
#include "Functions.h"
#include "Sprite.h"
#include "AudioSample.h"

using namespace std;

class ConsoleGame
{
public:
	ConsoleGame();
	virtual ~ConsoleGame();
	int ConstructConsole(int width, int height, int fontW, int fontH);
	void ChangeName(wstring name);
	void ShowCursor(bool value);
	void DisableSelection();
	void FixWindowSize();
	void DisableControlButton(bool close, bool min, bool max);
	void Clip(int &x, int &y);
	void Draw(int x, int y, short c, short col);
	void Fill(int x1, int y1, int x2, int y2, short c, short col);
	void DrawString(int x, int y, wstring c, short col);
	void DrawStringAlpha(int x, int y, wstring c, short col);
	void DrawLine(int x1, int y1, int x2, int y2, short c, short col);
	void DrawRectangle(int x, int y, int width, int height, short c, short col);
	void FillRectangle(int x, int y, int width, int height, short c, short col);
	void DrawSprite(int x, int y, Sprite sprite, short col);
	void Start();
	int ScreenWidth();
	int ScreenHeight();

private:
	void GameThread();

protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fDeltaTime);
	virtual bool OnUserDestroy();

protected:
	struct sKeyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	} m_keys[256];

public:
	sKeyState GetKey(int nKeyID);

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;

	CHAR_INFO *m_buffScreen;
	wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_originalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;

	short m_keyOldState[256] = {0};
	short m_keyNewState[256] = {0};

	bool m_bAtomActive;
};