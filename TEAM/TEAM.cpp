#include <iostream>
#include "Win.h"

using namespace std;

class Game : public ConsoleGame
{
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

bool Game::OnUserCreate()
{
	this->m_nCurrentState = 1;
	return true;
}

bool Game::OnUserUpdate(float fDeltaTime)
{
	return SceneManager(fDeltaTime);
}

bool Game::SceneManager(float fDeltaTime)
{
	switch (m_nCurrentState)
	{
	case 0:
		return false;

	case 1:
		StartMenu(fDeltaTime);
		break;
	case 2:
		PlayGame(fDeltaTime);
		break;

	case 3:
		LoadGame(fDeltaTime);
		break;

	case 4:
		HighScoreScene(fDeltaTime);
		break;

	case 5:
		InstructionScene(fDeltaTime);
		break;

	default:
		this->m_nCurrentState = 0;
		break;
	}
	return true;
}

void Game::StartMenu(float fDeltaTime)
{
	static int selectCurrent = 0;
	if ((this->m_keys['W'].bPressed || this->m_keys[VK_UP].bPressed) && selectCurrent > 0)
	{
		selectCurrent--;
	}
	if ((this->m_keys['S'].bPressed || this->m_keys[VK_DOWN].bPressed) && selectCurrent < 4)
	{
		selectCurrent++;
	}
	if (this->m_keys[VK_SPACE].bPressed || this->m_keys[VK_RETURN].bPressed)
	{
		switch (selectCurrent)
		{
		case 0:
			this->m_nCurrentState = 2;
			return;

		case 1:
			this->m_nCurrentState = 3;
			return;

		case 2:
			this->m_nCurrentState = 4;
			return;

		case 3:
			this->m_nCurrentState = 5;
			return;

		case 4:
			this->m_nCurrentState = 0;
			return;

		default:
			break;
		}
	}
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		m_nCurrentState = 0;
		return;
	}
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	static bool change = 0;
	static float time = 2;
	wstring title = L"";
	// title += L"█▀▀█  █▀▀█  █▀▀▀█  █▀▀▀█  █▀▀▀█ ▀█▀  █▄  █  █▀▀█    █▀▀█  █▀▀▀█  █▀▀█  █▀▀▄\n";
	// title += L"█     █▄▄▀  █   █  ▀▀▀▄▄  ▀▀▀▄▄  █   █ █ █  █ ▄▄    █▄▄▀  █   █  █▄▄█  █  █\n";
	// title += L"█▄▄█  █  █  █▄▄▄█  █▄▄▄█  █▄▄▄█ ▄█▄  █  ▀█  █▄▄█    █  █  █▄▄▄█  █  █  █▄▄▀\n";
	/*
░█████╗░██████╗░░█████╗░░██████╗░██████╗██╗███╗░░██╗░██████╗░  ██████╗░░█████╗░░█████╗░██████╗░
██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██║████╗░██║██╔════╝░  ██╔══██╗██╔══██╗██╔══██╗██╔══██╗
██║░░╚═╝██████╔╝██║░░██║╚█████╗░╚█████╗░██║██╔██╗██║██║░░██╗░  ██████╔╝██║░░██║███████║██║░░██║
██║░░██╗██╔══██╗██║░░██║░╚═══██╗░╚═══██╗██║██║╚████║██║░░╚██╗  ██╔══██╗██║░░██║██╔══██║██║░░██║
╚█████╔╝██║░░██║╚█████╔╝██████╔╝██████╔╝██║██║░╚███║╚██████╔╝  ██║░░██║╚█████╔╝██║░░██║██████╔╝
░╚════╝░╚═╝░░╚═╝░╚════╝░╚═════╝░╚═════╝░╚═╝╚═╝░░╚══╝░╚═════╝░  ╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚═════╝░
	*/
	title += L"░█████╗░██████╗░░█████╗░░██████╗░██████╗██╗███╗░░██╗░██████╗░  ██████╗░░█████╗░░█████╗░██████╗░\n";
	title += L"██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██║████╗░██║██╔════╝░  ██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n";
	title += L"██║░░╚═╝██████╔╝██║░░██║╚█████╗░╚█████╗░██║██╔██╗██║██║░░██╗░  ██████╔╝██║░░██║███████║██║░░██║\n";
	title += L"██║░░██╗██╔══██╗██║░░██║░╚═══██╗░╚═══██╗██║██║╚████║██║░░╚██╗  ██╔══██╗██║░░██║██╔══██║██║░░██║\n";
	title += L"╚█████╔╝██║░░██║╚█████╔╝██████╔╝██████╔╝██║██║░╚███║╚██████╔╝  ██║░░██║╚█████╔╝██║░░██║██████╔╝\n";
	title += L"░╚════╝░╚═╝░░╚═╝░╚════╝░╚═════╝░╚═════╝░╚═╝╚═╝░░╚══╝░╚═════╝░  ╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚═════╝░\n";

	static short titleColor = FG_GREEN + BG_DARK_RED;

	if (time >= 0.5)
	{
		if (change)
		{
			titleColor = FG_GREEN + BG_DARK_BLUE;
		}
		else
		{
			titleColor = FG_BLUE + BG_DARK_YELLOW;
		}
		time = 0;
		change = !change;
	}
	time += fDeltaTime;
	FillRectangle((this->m_nScreenWidth - 95) / 2 - 1, 4, 97, 8, L' ', titleColor);
	DrawString((this->m_nScreenWidth - 95) / 2, 5, title, titleColor);

	static short defaultColor = FG_WHITE + BG_CYAN;
	static short selectColor = FG_MAGENTA + BG_CYAN;

	/*
█▄ █ █▀▀ █ █ █   █▀▀ ▄▀█ █▀▄▀█ █▀▀
█ ▀█ ██▄ ▀▄▀▄▀   █▄█ █▀█ █ ▀ █ ██▄
	*/
	short newGameColor = selectCurrent == 0 ? selectColor : defaultColor;
	wstring newGame = L"";
	newGame += L"█▄ █ █▀▀ █ █ █   █▀▀ ▄▀█ █▀▄▀█ █▀▀\n";
	newGame += L"█ ▀█ ██▄ ▀▄▀▄▀   █▄█ █▀█ █ ▀ █ ██▄\n";
	DrawString((this->m_nScreenWidth - 34) / 2, 20, newGame, newGameColor);

	/*
█   █▀█ ▄▀█ █▀▄   █▀▀ ▄▀█ █▀▄▀█ █▀▀
█▄▄ █▄█ █▀█ █▄▀   █▄█ █▀█ █ ▀ █ ██▄
	*/
	short loadGameColor = selectCurrent == 1 ? selectColor : defaultColor;
	wstring loadGame = L"";
	loadGame += L"█   █▀█ ▄▀█ █▀▄   █▀▀ ▄▀█ █▀▄▀█ █▀▀\n";
	loadGame += L"█▄▄ █▄█ █▀█ █▄▀   █▄█ █▀█ █ ▀ █ ██▄\n";
	DrawString((this->m_nScreenWidth - 34) / 2, 25, loadGame, loadGameColor);

	/*
█ █ █ █▀▀ █ █   █▀ █▀▀ █▀█ █▀█ █▀▀
█▀█ █ █▄█ █▀█   ▄█ █▄▄ █▄█ █▀▄ ██▄
	*/
	short highScoreColor = selectCurrent == 2 ? selectColor : defaultColor;
	wstring highScore = L"";
	highScore += L"█ █ █ █▀▀ █ █   █▀ █▀▀ █▀█ █▀█ █▀▀\n";
	highScore += L"█▀█ █ █▄█ █▀█   ▄█ █▄▄ █▄█ █▀▄ ██▄\n";
	DrawString((this->m_nScreenWidth - 34) / 2, 30, highScore, highScoreColor);

	/*
█ █▄ █ █▀ ▀█▀ █▀█ █ █ █▀▀ ▀█▀ █ █▀█ █▄ █
█ █ ▀█ ▄█  █  █▀▄ █▄█ █▄▄  █  █ █▄█ █ ▀█
	*/
	short instructionColor = selectCurrent == 3 ? selectColor : defaultColor;
	wstring instruction = L"";
	instruction += L"█ █▄ █ █▀ ▀█▀ █▀█ █ █ █▀▀ ▀█▀ █ █▀█ █▄ █\n";
	instruction += L"█ █ ▀█ ▄█  █  █▀▄ █▄█ █▄▄  █  █ █▄█ █ ▀█\n";
	DrawString((this->m_nScreenWidth - 40) / 2, 35, instruction, instructionColor);

	/*
█▀▀ ▀▄▀ █ ▀█▀
██▄ █ █ █  █
	*/
	short exitColor = selectCurrent == 4 ? selectColor : defaultColor;
	wstring exit = L"";
	exit += L"█▀▀ ▀▄▀ █ ▀█▀\n";
	exit += L"██▄ █ █ █  █ \n";
	DrawString((this->m_nScreenWidth - 13) / 2, 40, exit, exitColor);

	Fill(0, 49, this->m_nScreenWidth - 1, 49 + 16, L' ', FG_BLACK + BG_BLACK);
	DrawLine(0, 49 + 8, this->m_nScreenWidth - 1, 49 + 8, L' ', FG_WHITE + BG_WHITE);
	/*
	  ▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▌
   ▄▄██▌█░░░░░░░░░░░░▐
▄▄▄▌▐██▌█░░░░░░░░░░░░▐
███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▌
▀@▀▀▀▀▀▀▀@@▀▀▀▀▀▀@@▀
	*/
	static float truck1X = 0;
	short truck1Color = FG_RED + BG_BLACK;
	truck1X += fDeltaTime * -20;
	if (truck1X < -25)
	{
		truck1X = (float)this->m_nScreenWidth + 1;
	}
	wstring truck1 = L"";
	truck1 += L"      ▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▌ \n";
	truck1 += L"   ▄▄██▌█░░░░░░░░░░░░▐ \n";
	truck1 += L"▄▄▄▌▐██▌█░░░░░░░░░░░░▐ \n";
	truck1 += L"███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▌ \n";
	truck1 += L"▀@▀▀▀▀▀▀▀@@▀▀▀▀▀▀@@▀   \n";
	DrawStringAlpha((int)truck1X, 50, truck1, truck1Color);

	/*
▌▀▀▀▀▀▀▀▀▀▀▀▀▐▌▄
▐░░░░░░░░░░░░█▌██▄▄
▐░░░░░░░░░░░░█▌██▐▌▄▄▄
▌▄▄▄▄▄▄▄▄▄▄▄▄█▌███████
  ▀@@▀▀▀▀▀▀@@▀▀▀▀▀▀▀@▀
	*/
	short truck2Color = FG_GREEN + BG_BLACK;
	static float truck2X = 0;
	truck2X += fDeltaTime * 40;
	if (truck2X > this->m_nScreenWidth + 25)
	{
		truck2X = -25;
	}
	wstring truck2 = L"";
	truck2 += L"▌▀▀▀▀▀▀▀▀▀▀▀▀▐▌▄       \n";
	truck2 += L"▐░░░░░░░░░░░░█▌██▄▄    \n";
	truck2 += L"▐░░░░░░░░░░░░█▌██▐▌▄▄▄ \n";
	truck2 += L"▌▄▄▄▄▄▄▄▄▄▄▄▄█▌███████ \n";
	truck2 += L"  ▀@@▀▀▀▀▀▀@@▀▀▀▀▀▀▀@▀ \n";
	DrawStringAlpha((int)truck2X, 60, truck2, truck2Color);
}

void Game::PlayGame(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_WHITE);
	DrawRectangle(90, 0, 30, this->m_nScreenHeight, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	Fill(0, 0, 89, 7, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);
	DrawLine(0, 8, 89, 8, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 14, 89, 14, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 20, 89, 20, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 26, 89, 26, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 32, 89, 32, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 38, 89, 38, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 44, 89, 44, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 50, 89, 50, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 56, 89, 56, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 62, 89, 62, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	Fill(0, 63, 89, 69, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);

	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

void Game::LoadGame(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

void Game::HighScoreScene(float fDeltaTime)
{
	/*
██╗░░██╗██╗░██████╗░██╗░░██╗  ░██████╗░█████╗░░█████╗░██████╗░███████╗
██║░░██║██║██╔════╝░██║░░██║  ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝
███████║██║██║░░██╗░███████║  ╚█████╗░██║░░╚═╝██║░░██║██████╔╝█████╗░░
██╔══██║██║██║░░╚██╗██╔══██║  ░╚═══██╗██║░░██╗██║░░██║██╔══██╗██╔══╝░░
██║░░██║██║╚██████╔╝██║░░██║  ██████╔╝╚█████╔╝╚█████╔╝██║░░██║███████╗
╚═╝░░╚═╝╚═╝░╚═════╝░╚═╝░░╚═╝  ╚═════╝░░╚════╝░░╚════╝░╚═╝░░╚═╝╚══════╝
	*/

	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	wstring title = L"";
	title += L"██╗░░██╗██╗░██████╗░██╗░░██╗  ░██████╗░█████╗░░█████╗░██████╗░███████╗\n";
	title += L"██║░░██║██║██╔════╝░██║░░██║  ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝\n";
	title += L"███████║██║██║░░██╗░███████║  ╚█████╗░██║░░╚═╝██║░░██║██████╔╝█████╗░░\n";
	title += L"██╔══██║██║██║░░╚██╗██╔══██║  ░╚═══██╗██║░░██╗██║░░██║██╔══██╗██╔══╝░░\n";
	title += L"██║░░██║██║╚██████╔╝██║░░██║  ██████╔╝╚█████╔╝╚█████╔╝██║░░██║███████╗\n";
	title += L"╚═╝░░╚═╝╚═╝░╚═════╝░╚═╝░░╚═╝  ╚═════╝░░╚════╝░░╚════╝░╚═╝░░╚═╝╚══════╝";
	static bool change = 0;
	static float time = 2;
	static short titleColor = FG_GREEN + BG_DARK_RED;

	if (time >= 0.5)
	{
		if (change)
		{
			titleColor = FG_GREEN + BG_DARK_BLUE;
		}
		else
		{
			titleColor = FG_BLUE + BG_DARK_YELLOW;
		}
		time = 0;
		change = !change;
	}
	time += fDeltaTime;
	FillRectangle((this->m_nScreenWidth - 70) / 2 - 1, 4, 72, 8, L' ', titleColor);
	DrawString((this->m_nScreenWidth - 70) / 2, 5, title, titleColor);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

void Game::InstructionScene(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

int main()
{
	Game game;
	if (!game.ConstructConsole(120,70, 9, 9))
	{
		game.ChangeName(L"Game");
		game.Start();
	}
	return 0;
}
