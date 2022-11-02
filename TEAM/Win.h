#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>
#include <thread>
#include <deque>
#include <fstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <random>

using namespace std;

enum COLOR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, // Thanks MS :-/
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};

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

string WstringToString(wstring wstr);
wstring StringToWstring(string str);