#include "Win.h"

ConsoleGame::ConsoleGame()
{
	this->m_nScreenWidth = 80;
	this->m_nScreenHeight = 30;

	this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	memset(this->m_keyOldState, 0, 256 * sizeof(short));
	memset(this->m_keyNewState, 0, 256 * sizeof(short));
	memset(this->m_keys, 0, 256 * sizeof(sKeyState));

	this->m_sAppName = L"Default";
}

ConsoleGame::~ConsoleGame()
{
	SetConsoleActiveScreenBuffer(m_hOriginalConsole);
	delete[] this->m_buffScreen;
}

int ConsoleGame::ConstructConsole(int width, int height, int fontW, int fontH)
{
	if (this->m_hConsole == INVALID_HANDLE_VALUE)
		return 1;

	this->m_nScreenWidth = width;
	this->m_nScreenHeight = height;

	this->m_buffScreen = new CHAR_INFO[this->m_nScreenWidth * this->m_nScreenHeight];
	memset(this->m_buffScreen, 0, sizeof(CHAR_INFO) * this->m_nScreenWidth * this->m_nScreenHeight);

	this->m_rectWindow.Left = 0;
	this->m_rectWindow.Top = 0;
	this->m_rectWindow.Right = 1;
	this->m_rectWindow.Bottom = 1;
	SetConsoleWindowInfo(this->m_hConsole, FALSE, &this->m_rectWindow);

	COORD coord;
	coord.X = this->m_nScreenWidth;
	coord.Y = this->m_nScreenHeight;
	if (!SetConsoleScreenBufferSize(this->m_hConsole, coord))
	{
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(this->m_hConsole))
	{
		return 1;
	}

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontW;
	cfi.dwFontSize.Y = fontH;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(this->m_hConsole, FALSE, &cfi))
	{
		return 1;
	}

	this->m_rectWindow.Left = 0;
	this->m_rectWindow.Top = 0;
	this->m_rectWindow.Right = this->m_nScreenWidth - 1;
	this->m_rectWindow.Bottom = this->m_nScreenHeight - 1;
	ShowCursor(false);

	if (!SetConsoleWindowInfo(this->m_hConsole, TRUE, &this->m_rectWindow))
	{
		return 1;
	}

	if (!SetConsoleMode(this->m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
	{
		return 1;
	}
	DisableSelection();
	FixWindowSize();
	DisableControlButton(false, false, true);
	return 0;
}

void ConsoleGame::ChangeName(wstring name)
{
	this->m_sAppName = name;
}

void ConsoleGame::ShowCursor(bool value)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = value;
	cursorInfo.dwSize = 10;
	SetConsoleCursorInfo(this->m_hConsole, &cursorInfo);
}

void ConsoleGame::DisableSelection()
{
	SetConsoleMode(this->m_hConsoleIn, ~ENABLE_QUICK_EDIT_MODE);
}

void ConsoleGame::FixWindowSize()
{
	HWND hwnd = GetConsoleWindow();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void ConsoleGame::DisableControlButton(bool close, bool min, bool max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void ConsoleGame::Clip(int& x, int& y)
{
	if (x < 0)
		x = 0;
	if (x >= this->m_nScreenWidth)
		x = this->m_nScreenWidth - 1;
	if (y < 0)
		y = 0;
	if (y >= this->m_nScreenHeight)
		y = this->m_nScreenHeight - 1;
}

void ConsoleGame::Draw(int x, int y, short c, short col)
{
	if (x >= 0 && x < this->m_nScreenWidth && y >= 0 && y < this->m_nScreenHeight)
	{
		this->m_buffScreen[y * this->m_nScreenWidth + x].Char.UnicodeChar = c;
		this->m_buffScreen[y * this->m_nScreenWidth + x].Attributes = col;
	}
}

void ConsoleGame::Fill(int x1, int y1, int x2, int y2, short c, short col)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			Draw(x, y, c, col);
		}
	}
}

void ConsoleGame::DrawString(int x, int y, wstring c, short col)
{
	int newLine = 0;
	int t = 0;
	for (size_t i = 0; i < c.size(); i++)
	{
		if (c[i] == L'\n')
		{
			newLine++;
			t = 0;
		}
		else
		{
			Draw(x + t, y + newLine, c[i], col);
			t++;
		}
	}
}

void ConsoleGame::DrawStringAlpha(int x, int y, wstring c, short col)
{
	int newLine = 0;
	int t = 0;
	for (size_t i = 0; i < c.size(); i++)
	{
		if (c[i] == L'\n')
		{
			newLine++;
			t = 0;
		}
		else if (c[i] == L' ')
		{
			t++;
		}
		else
		{
			Draw(x + t, y + newLine, c[i], col);
			t++;
		}
	}
}

void ConsoleGame::DrawLine(int x1, int y1, int x2, int y2, short c, short col)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		Draw(x, y, c, col);

		for (int i = 0; x < xe; i++)
		{
			x++;
			if (px < 0)
			{
				px += 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y++;
				}
				else
				{
					y--;
				}
				px += 2 * (dy1 - dx1);
			}
			Draw(x, y, c, col);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}

		Draw(x, y, c, col);
		for (i = 0; y < ye; i++)
		{
			y++;
			if (py <= 0)
			{
				py += 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x++;
				}
				else
				{
					x--;
				}
				py += 2 * (dx1 - dy1);
			}
			Draw(x, y, c, col);
		}
	}
}


void ConsoleGame::DrawRectangle(int x, int y, int width, int height, short c, short col)
{
	for (int i = x; i < x + width; i++)
	{
		Draw(i, y, c, col);
		Draw(i, y + height - 1, c, col);
	}
	for (int j = y; j < y + height; j++)
	{
		Draw(x, j, c, col);
		Draw(x + width - 1, j, c, col);
	}
}

void ConsoleGame::FillRectangle(int x, int y, int width, int height, short c, short col)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			Draw(i, j, c, col);
		}
	}
}

void ConsoleGame::Start()
{
	this->m_bAtomActive = true;
	thread t = thread(&ConsoleGame::GameThread, this);

	t.join();
}

void ConsoleGame::GameThread()
{
	OnUserCreate();
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (this->m_bAtomActive)
	{
		while (this->m_bAtomActive)
		{
			tp2 = chrono::system_clock::now();
			chrono::duration<float> deltaTime = tp2 - tp1;
			tp1 = tp2;
			float fDeltaTime = deltaTime.count();

			for (int i = 0; i < 256; i++)
			{
				this->m_keyNewState[i] = GetAsyncKeyState(i);

				this->m_keys[i].bPressed = false;
				this->m_keys[i].bReleased = false;

				if (this->m_keyNewState[i] != m_keyOldState[i])
				{
					if (this->m_keyNewState[i] & 0x8000)
					{
						this->m_keys[i].bPressed = !this->m_keys[i].bHeld;
						m_keys[i].bHeld = true;
					}
					else
					{
						this->m_keys[i].bReleased = true;
						this->m_keys[i].bHeld = false;
					}
				}

				this->m_keyOldState[i] = this->m_keyNewState[i];
			}

			if (!OnUserUpdate(fDeltaTime))
				m_bAtomActive = false;
			wchar_t s[256];
			swprintf_s(s, 256, L"%s - FPS = %3.2f", this->m_sAppName.c_str(), 1.0f / fDeltaTime);
			SetConsoleTitle(s);
			COORD dwBufferSize;
			dwBufferSize.X = this->m_nScreenWidth;
			dwBufferSize.Y = this->m_nScreenHeight;
			WriteConsoleOutput(this->m_hConsole, this->m_buffScreen, dwBufferSize, { 0, 0 }, &this->m_rectWindow);
		}
		if (!OnUserDestroy())
		{
			// User denied destroy for some reason, so continue running
			m_bAtomActive = true;
		}
	}
}

int ConsoleGame::ScreenWidth()
{
	return this->m_nScreenWidth;
}

int ConsoleGame::ScreenHeight()
{
	return this->m_nScreenHeight;
}

bool ConsoleGame::OnUserCreate()
{
	return true;
}
bool ConsoleGame::OnUserUpdate(float fDeltaTime)
{
	return true;
}
bool ConsoleGame::OnUserDestroy()
{
	return true;
}

ConsoleGame::sKeyState ConsoleGame::GetKey(int nKeyID)
{
	return this->m_keys[nKeyID];
}