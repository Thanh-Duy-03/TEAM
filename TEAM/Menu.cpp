#include "Menu.h"

bool Game::OnUserCreate()
{
	srand((unsigned int)time(NULL));
	LoadData("Save/HighScores.txt", highScores);
	LoadData("Save/LoadGames.txt", loadGames);
	this->m_nCurrentState = 1;
	this->player.Create();

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
	case 0: // Exit
	{
		return false;
	}

	case 1: // Menu
		StartMenu(fDeltaTime);
		break;
	case 2: // New Game
	{
		StartGame(fDeltaTime, 1, 0);
	}
	break;

	case 3: // Load game
		LoadGame(fDeltaTime);
		break;

	case 4: // High score
		HighScoreScene(fDeltaTime);
		break;

	case 5: // Instruction
		InstructionScene(fDeltaTime);
		break;

	case 6: // Play Game
		PlayGame(fDeltaTime);
		break;
	case 7:
		SaveGame(fDeltaTime);
		break;
	case 8:
		DieGame(fDeltaTime);
		break;
	default:
		this->m_nCurrentState = 0; //  Exit
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
░█████╗░██████╗  █████╗  ██████╗ ██████╗██╗███╗  ██╗ ██████╗   ██████╗  █████╗  █████╗ ██████╗
██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██║████╗ ██║██╔════╝   ██╔══██╗██╔══██╗██╔══██╗██╔══██╗
██║  ╚═╝██████╔╝██║  ██║╚█████╗ ╚█████╗ ██║██╔██╗██║██║  ██╗   ██████╔╝██║  ██║███████║██║  ██║
██║  ██╗██╔══██╗██║  ██║ ╚═══██╗ ╚═══██╗██║██║╚████║██║  ╚██╗  ██╔══██╗██║  ██║██╔══██║██║  ██║
╚█████╔╝██║  ██║╚█████╔╝██████╔╝██████╔╝██║██║ ╚███║╚██████╔╝  ██║  ██║╚█████╔╝██║  ██║██████╔╝
 ╚════╝ ╚═╝  ╚═╝ ╚════╝ ╚═════╝ ╚═════╝ ╚═╝╚═╝  ╚══╝ ╚═════╝   ╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝╚═════╝
	*/
	title += L" █████╗ ██████╗  █████╗  ██████╗ ██████╗██╗███╗  ██╗ ██████╗   ██████╗  █████╗  █████╗ ██████╗ \n";
	title += L"██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██║████╗ ██║██╔════╝   ██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n";
	title += L"██║  ╚═╝██████╔╝██║  ██║╚█████╗ ╚█████╗ ██║██╔██╗██║██║  ██╗   ██████╔╝██║  ██║███████║██║  ██║\n";
	title += L"██║  ██╗██╔══██╗██║  ██║ ╚═══██╗ ╚═══██╗██║██║╚████║██║  ╚██╗  ██╔══██╗██║  ██║██╔══██║██║  ██║\n";
	title += L"╚█████╔╝██║  ██║╚█████╔╝██████╔╝██████╔╝██║██║ ╚███║╚██████╔╝  ██║  ██║╚█████╔╝██║  ██║██████╔╝\n";
	title += L" ╚════╝ ╚═╝  ╚═╝ ╚════╝ ╚═════╝ ╚═════╝ ╚═╝╚═╝  ╚══╝ ╚═════╝   ╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝╚═════╝ \n";

	static short titleColor = FG_RED + BG_YELLOW;

	if (time >= 0.5)
	{
		if (change)
		{
			titleColor = FG_RED + BG_YELLOW;
		}
		else
		{
			titleColor = FG_MAGENTA + BG_WHITE;
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

void Game::StartGame(float fDeltaTime, int level, int score)
{
	this->score = 200;
	this->player.Set(0, 62, level, score);

	// Pavement
	this->lane[0].SetPosY(62);
	this->lane[0].SetLight(0);
	this->lane[0].SetBgColor(BG_DARK_GREY);

	this->lane[7].SetPosY(0);
	this->lane[7].SetLight(0);
	this->lane[7].SetBgColor(BG_DARK_GREY);

	// Roads
	this->lane[1].SetPosY(53);
	this->lane[1].SetStart(-20);
	this->lane[1].SetEnd(95);
	this->lane[1].SetLight(true);
	this->lane[1].SetSpeed(5.0f + rand() % 10);
	this->lane[1].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[1].SetFileName(L"Assets/Obstacles/Truck.txt");
	this->lane[1].SetBgColor(BG_WHITE);
	this->lane[1].Reset();

	this->lane[2].SetPosY(44);
	this->lane[2].SetStart(90);
	this->lane[2].SetEnd(-30);
	this->lane[2].SetLight(true);
	this->lane[2].SetSpeed(-5.0f - rand() % 10);
	this->lane[2].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[2].SetFileName(L"Assets/Obstacles/Truck2.txt");
	this->lane[2].SetBgColor(BG_WHITE);
	this->lane[2].Reset();

	this->lane[3].SetPosY(35);
	this->lane[3].SetStart(-20);
	this->lane[3].SetEnd(95);
	this->lane[3].SetLight(true);
	this->lane[3].SetSpeed(5.0f + rand() % 10);
	this->lane[3].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[3].SetFileName(L"Assets/Obstacles/Truck.txt");
	this->lane[3].SetBgColor(BG_WHITE);
	this->lane[3].Reset();

	this->lane[4].SetPosY(26);
	this->lane[4].SetStart(-20);
	this->lane[4].SetEnd(95);
	this->lane[4].SetLight(true);
	this->lane[4].SetSpeed(5.0f + rand() % 10);
	this->lane[4].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[4].SetFileName(L"Assets/Obstacles/Truck.txt");
	this->lane[4].SetBgColor(BG_WHITE);
	this->lane[4].Reset();

	this->lane[5].SetPosY(17);
	this->lane[5].SetStart(-20);
	this->lane[5].SetEnd(95);
	this->lane[5].SetLight(true);
	this->lane[5].SetSpeed(5.0f + rand() % 10);
	this->lane[5].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[5].SetFileName(L"Assets/Obstacles/Truck.txt");
	this->lane[5].SetBgColor(BG_WHITE);
	this->lane[5].Reset();

	this->lane[6].SetPosY(8);
	this->lane[6].SetStart(-20);
	this->lane[6].SetEnd(95);
	this->lane[6].SetLight(true);
	this->lane[6].SetSpeed(5.0f + rand() % 10);
	this->lane[6].SetDistance(60 - 6 * (this->player.GetLevel() % 5));
	this->lane[6].SetFileName(L"Assets/Obstacles/Truck.txt");
	this->lane[6].SetBgColor(BG_WHITE);
	this->lane[6].Reset();

	this->m_nCurrentState = 6;
}

void Game::PlayGame(float fDeltaTime)
{
	static float time = 0;
	int offsetX = 0;
	static float x = 0;
	static int ran = rand() % 6;

	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_WHITE);
	DrawLine(0, 8, 89, 8, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 62, 89, 62, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLanes();
	DrawRectangle(90, 0, 30, this->m_nScreenHeight, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	FillRectangle(91, 1, 28, this->m_nScreenHeight - 2, PIXEL_SOLID, FG_WHITE + BG_WHITE);

	this->player.SetBgColor(this->lane[this->player.GetCurrentLane()].GetBgColor());
	this->player.Draw(this);

	if (this->player.GetDie())
	{
		if (this->player.DieState(fDeltaTime))
		{
			this->m_nCurrentState = 8;
			return;
		}
	}
	else
	{
		this->player.IdleState(fDeltaTime);
	}

	DrawScore(fDeltaTime);
	if (this->player.GetCurrentLane() != 0 && this->player.GetCurrentLane() != 7 && this->lane[this->player.GetCurrentLane()].CheckCollider(&this->player))
	{
		this->player.SetDie(true);
	}
	// Qua mang choi

	if (this->player.GetCurrentLane() == 7)
	{
		this->player.SetLevel(this->player.GetLevel() + 1);
		this->player.SetScore(this->player.GetScore() + (int)this->score);
		StartGame(fDeltaTime, this->player.GetLevel(), this->player.GetScore());
		time = 0;
		x = 0;
		offsetX = 0;
		ran = rand() % 6;
	}
	if (!this->player.GetDie())
	{
		UpdateLane(fDeltaTime);
		if (this->m_keys[VK_ESCAPE].bPressed)
		{
			time = 0;
			x = 0;
			offsetX = 0;
			ran = rand() % 6;
			this->m_nCurrentState = 1;
			return;
		}
		if (time >= 3.0f)
		{
			if (this->m_keys['L'].bPressed)
			{
				this->m_nCurrentState = 7;
			}
			if ((this->m_keys['A'].bHeld || this->m_keys[VK_LEFT].bHeld) && this->player.GetPosX() >= 0)
			{
				this->player.Move(-20 * fDeltaTime, 0);
			}
			if ((this->m_keys['D'].bHeld || this->m_keys[VK_RIGHT].bHeld) && this->player.GetPosX() + this->player.GetWidth() <= 90)
			{
				this->player.Move(20 * fDeltaTime, 0);
			}
			if ((this->m_keys['W'].bPressed || this->m_keys[VK_UP].bPressed) && this->player.GetCurrentLane() < 7)
			{
				this->player.SetCurrentLane(this->player.GetCurrentLane() + 1);
				this->player.SetPosY(this->lane[this->player.GetCurrentLane()].GetY());
			}
			if ((this->m_keys['S'].bPressed || this->m_keys[VK_DOWN].bPressed) && this->player.GetCurrentLane() > 0)
			{
				this->player.SetCurrentLane(this->player.GetCurrentLane() - 1);
				this->player.SetPosY(this->lane[this->player.GetCurrentLane()].GetY());
			}
		}
		else if (time >= 1.5f)
		{
			Alphabet a;
			string sen[] = {
				"press w to up",
				"press s to down",
				"press a to go left",
				"press d to go right",
				"press l to save game",
				"press esc to escape"};
			string wait = sen[ran];
			for (int i = 0; i < wait.length(); i++)
			{
				if (wait[i] <= 'z' && wait[i] >= 'a')
				{
					DrawStringAlpha(x + offsetX, 3, a.alphabet[wait[i] - 'a'], FG_RED + BG_DARK_GREY);
					offsetX += a.SizeAlphabet[wait[i] - 'a'];
				}
				else if (wait[i] == ' ')
				{
					offsetX += 3;
				}
			}
			x += 20 * fDeltaTime;
			if (x + offsetX >= 90)
			{
				x = 90 - offsetX;
			}
		}

		time += fDeltaTime;
	}
	else
	{
		time = 0;
		x = 0;
		offsetX = 0;
		ran = rand() % 6;
	}
}

void Game::LoadGame(float fDeltaTime)
{
	/*
		██╗░░░░░░█████╗░░█████╗░██████╗░  ░██████╗░░█████╗░███╗░░░███╗███████╗
		██║░░░░░██╔══██╗██╔══██╗██╔══██╗  ██╔════╝░██╔══██╗████╗░████║██╔════╝
		██║░░░░░██║░░██║███████║██║░░██║  ██║░░██╗░███████║██╔████╔██║█████╗░░
		██║░░░░░██║░░██║██╔══██║██║░░██║  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░
		███████╗╚█████╔╝██║░░██║██████╔╝  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗
		╚══════╝░╚════╝░╚═╝░░╚═╝╚═════╝░  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝
	*/
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	wstring title = L"";
	title += L"██╗      █████╗  █████╗ ██████╗    ██████╗  █████╗ ███╗   ███╗███████╗\n";
	title += L"██║     ██╔══██╗██╔══██╗██╔══██╗  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
	title += L"██║     ██║  ██║███████║██║  ██║  ██║  ██╗ ███████║██╔████╔██║█████╗  \n";
	title += L"██║     ██║  ██║██╔══██║██║  ██║  ██║  ╚██╗██╔══██║██║╚██╔╝██║██╔══╝  \n";
	title += L"███████╗╚█████╔╝██║  ██║██████╔╝  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
	title += L"╚══════╝ ╚════╝ ╚═╝  ╚═╝╚═════╝    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝";
	static bool change = 0;
	static float time = 2;
	static short titleColor = FG_RED + BG_YELLOW;

	if (time >= 0.5)
	{
		if (change)
		{
			titleColor = FG_RED + BG_YELLOW;
		}
		else
		{
			titleColor = FG_WHITE + BG_DARK_BLUE;
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
		return;
	}
	static int vtLoadGame = 0;
	if ((this->m_keys['W'].bPressed || this->m_keys[VK_UP].bPressed) && vtLoadGame > 0)
	{
		--vtLoadGame;
	}
	if ((this->m_keys['S'].bPressed || this->m_keys[VK_DOWN].bPressed) && vtLoadGame < 4)
	{
		++vtLoadGame;
	}
	if (this->m_keys[VK_SPACE].bPressed || this->m_keys[VK_RETURN].bPressed)
	{
		StartGame(fDeltaTime, this->loadGames[vtLoadGame].level, this->loadGames[vtLoadGame].point);
	}

	DrawLoadGame(fDeltaTime, vtLoadGame);
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
	title += L"██╗  ██╗██╗ ██████╗ ██╗  ██╗   ██████╗ █████╗  █████╗ ██████╗ ███████╗\n";
	title += L"██║  ██║██║██╔════╝ ██║  ██║  ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝\n";
	title += L"███████║██║██║  ██╗ ███████║  ╚█████╗ ██║  ╚═╝██║  ██║██████╔╝█████╗  \n";
	title += L"██╔══██║██║██║  ╚██╗██╔══██║   ╚═══██╗██║  ██╗██║  ██║██╔══██╗██╔══╝  \n";
	title += L"██║  ██║██║╚██████╔╝██║  ██║  ██████╔╝╚█████╔╝╚█████╔╝██║  ██║███████╗\n";
	title += L"╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝  ╚═════╝  ╚════╝  ╚════╝ ╚═╝  ╚═╝╚══════╝";
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

	DrawHighScore(fDeltaTime);
}

void Game::InstructionScene(float fDeltaTime)
{

	/*
██╗███╗░░██╗░██████╗████████╗██████╗░██╗░░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗
██║████╗░██║██╔════╝╚══██╔══╝██╔══██╗██║░░░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
██║██╔██╗██║╚█████╗░░░░██║░░░██████╔╝██║░░░██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║
██║██║╚████║░╚═══██╗░░░██║░░░██╔══██╗██║░░░██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║
██║██║░╚███║██████╔╝░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║
╚═╝╚═╝░░╚══╝╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝
	*/

	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	wstring title = L"";
	title += L"██╗███╗░░██╗░██████╗████████╗██████╗░██╗░░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗\n";
	title += L"██║████╗░██║██╔════╝╚══██╔══╝██╔══██╗██║░░░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║\n";
	title += L"██║██╔██╗██║╚█████╗░░░░██║░░░██████╔╝██║░░░██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║\n";
	title += L"██║██║╚████║░╚═══██╗░░░██║░░░██╔══██╗██║░░░██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║\n";
	title += L"██║██║░╚███║██████╔╝░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║\n";
	title += L"╚═╝╚═╝░░╚══╝╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝";
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
	FillRectangle((this->m_nScreenWidth - 81) / 2 - 1, 4, 85, 8, L' ', titleColor);
	DrawString((this->m_nScreenWidth - 81) / 2, 5, title, titleColor);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

void Game::UpdateLane(float fDeltaTime)
{
	for (int i = 1; i < 7; i++)
	{
		this->lane[i].Update(fDeltaTime);
	}
}
void Game::DrawLanes()
{
	this->lane[7].Draw(this);
	for (int i = 0; i < 7; i++)
	{
		this->lane[i].Draw(this);
	}
}
void Game::DrawScore(float fDeltaTime)
{
	wstring Score = L"█▀ █▀▀ █▀█ █▀█ █▀▀\n";
	Score += L"▄█ █▄▄ █▄█ █▀▄ ██▄";
	DrawString(93, 7, Score, BG_WHITE + FG_BLUE);
	wstring Number0 = L"█▀▀█\n█▄▀█\n█▄▄█";
	wstring Number1 = L"▄█\n █\n▄█▄";
	wstring Number2 = L"█▀█\n ▄▀\n█▄▄";
	wstring Number3 = L"█▀▀█\n  ▀▄\n█▄▄█";
	wstring Number4 = L" █▀█\n█▄▄█▄\n   █";
	wstring Number5 = L"█▀▀\n▀▀▄\n▄▄▀";
	wstring Number6 = L"▄▀▀▄\n█▄▄\n▀▄▄▀";
	wstring Number7 = L"▀▀▀█\n  █\n ▐▌";
	wstring Number8 = L"▄▀▀▄\n▄▀▀▄\n▀▄▄▀";
	wstring Number9 = L"▄▀▀▄\n▀▄▄█\n ▄▄▀";
	wstring Numbers[10] = {Number0, Number1, Number2, Number3, Number4, Number5, Number6, Number7, Number8, Number9};
	this->score -= (fDeltaTime * 1.5f);
	int k = this->score;
	for (int i = 1; i <= 3; i++)
	{
		DrawString(112 - 5 * i, 12, Numbers[k % 10], BG_WHITE + FG_BLUE);
		k /= 10;
	}

	int j = this->player.GetScore();
	for (int i = 1; i <= 3; i++)
	{
		DrawString(112 - 5 * i, 19, Numbers[j % 10], BG_WHITE + FG_BLUE);
		j /= 10;
	}
	DrawString(112 - 5, 25, Numbers[this->player.GetLevel() % 10], BG_WHITE + FG_BLUE);

	if (this->score <= 0)
	{
		this->m_nCurrentState = 1;
	}
	/*	█▀▀█   ▄█░   █▀█   █▀▀█   ░█▀█░   █▀▀   ▄▀▀▄   ▀▀▀█   ▄▀▀▄   ▄▀▀▄
		█▄▀█   ░█░   ░▄▀   ░░▀▄   █▄▄█▄   ▀▀▄   █▄▄░   ░░█░   ▄▀▀▄   ▀▄▄█
		█▄▄█   ▄█▄   █▄▄   █▄▄█   ░░░█░   ▄▄▀   ▀▄▄▀   ░▐▌░   ▀▄▄▀   ░▄▄▀*/
}

void Game::DrawLoadGame(float fDeltaTime, int Vt)
{
	static short BG = BG_YELLOW;
	static short FG = FG_MAGENTA;

	FillRectangle(12, 22, 97, 40, L' ', BG);

	static short BG_MUC = BG_GREEN;
	static short FG_MUC = FG_MAGENTA;
	static bool change = 0;
	static float time = 0;
	// BG_MUC = BG_GREEN;
	if (time >= 0.4)
	{
		if (change)
		{
			BG_MUC = BG_GREEN;
		}
		else
		{
			BG_MUC = BG_WHITE;
		}
		time = 0;
		change = !change;
	}
	time += fDeltaTime;
	FillRectangle(13, 24, 95, 4, L' ', BG_MUC);
	/*
█▄░█ ▄▀█ █▀▄▀█ █▀▀
█░▀█ █▀█ █░▀░█ ██▄
	*/
	wstring Name = L"█▄ █ ▄▀█ █▀▄▀█ █▀▀\n";
	Name += L"█ ▀█ █▀█ █ ▀ █ ██▄";
	DrawString(15, 25, Name, BG_MUC + FG_MUC);

	/*

█▀ █▀▀ █▀█ █▀█ █▀▀
▄█ █▄▄ █▄█ █▀▄ ██▄
	*/
	wstring Score = L"█▀ █▀▀ █▀█ █▀█ █▀▀\n";
	Score += L"▄█ █▄▄ █▄█ █▀▄ ██▄";
	DrawString(56, 25, Score, BG_MUC + FG_MUC);

	/*

█░░ █▀▀ █░█ █▀▀ █░░
█▄▄ ██▄ ▀▄▀ ██▄ █▄▄
	*/
	wstring Level = L"█   █▀▀ █ █ █▀▀ █ \n";
	Level += L"█▄▄ ██▄ ▀▄▀ ██▄ █▄▄";
	DrawString(87, 25, Level, BG_MUC + FG_MUC);

	Alphabet a;
	int y = 35;
	for (int i = 0; i < this->loadGames.size(); ++i)
	{
		int x = 15;

		if (i == Vt)
		{
			BG = BG_GREY;
			FillRectangle(13, 35 + Vt * 5 - 1, 95, 4, L' ', BG);
		}

		for (int j = 0; j < this->loadGames[i].name.length(); ++j)
		{
			wstring name = L"";
			if (this->loadGames[i].name[j] >= 'A' && this->loadGames[i].name[j] <= 'Z')
			{
				name = a.alphabet[this->loadGames[i].name[j] - 'A'];
				DrawString(x, y, name, BG + FG);
				x = x + a.SizeAlphabet[this->loadGames[i].name[j] - 'A'];
			}
			if (this->loadGames[i].name[j] >= '0' && this->loadGames[i].name[j] <= '9')
			{
				name = a.Numbers[this->loadGames[i].name[j] - '0'];
				DrawString(x, y, name, BG + FG);
				x = x + a.SizeNumbers[this->loadGames[i].name[j] - '0'];
			}
		}

		int Score = this->loadGames[i].point;
		wstring SCORE[5];
		int SizeScore[5];
		int z = 0;
		do
		{
			SCORE[z] = a.Numbers[Score % 10];
			SizeScore[z] = a.SizeNumbers[Score % 10];
			Score = Score / 10;
			++z;
		} while (Score > 0);
		x = 60;
		while (z > 0)
		{
			DrawString(x, y, SCORE[z - 1], BG + FG);
			x = x + SizeScore[z - 1];
			--z;
		}

		x = 95;
		DrawString(x, y, a.Numbers[this->loadGames[i].level], BG + FG);
		x = x + a.SizeNumbers[this->loadGames[i].level];

		y = y + 5;
		BG = BG_YELLOW;
	}
}

void Game::DrawHighScore(float fDeltaTime)
{
	static short BG = BG_YELLOW;
	static short FG = FG_MAGENTA;

	FillRectangle(12, 22, 97, 40, L' ', BG);

	static short BG_MUC = BG_GREEN;
	static short FG_MUC = FG_MAGENTA;
	static bool change = 0;
	static float time = 2;
	// BG_MUC = BG_GREEN;
	if (time >= 0.4)
	{
		if (change)
		{
			BG_MUC = BG_GREEN;
		}
		else
		{
			BG_MUC = BG_WHITE;
		}
		time = 0;
		change = !change;
	}
	time += fDeltaTime;
	FillRectangle(13, 24, 95, 4, L' ', BG_MUC);
	/*
█▄░█ ▄▀█ █▀▄▀█ █▀▀
█░▀█ █▀█ █░▀░█ ██▄
	*/
	wstring Name = L"█▄ █ ▄▀█ █▀▄▀█ █▀▀\n";
	Name += L"█ ▀█ █▀█ █ ▀ █ ██▄";
	DrawString(15, 25, Name, BG_MUC + FG_MUC);

	/*

█▀ █▀▀ █▀█ █▀█ █▀▀
▄█ █▄▄ █▄█ █▀▄ ██▄
	*/
	wstring Score = L"█▀ █▀▀ █▀█ █▀█ █▀▀\n";
	Score += L"▄█ █▄▄ █▄█ █▀▄ ██▄";
	DrawString(56, 25, Score, BG_MUC + FG_MUC);

	/*

█░░ █▀▀ █░█ █▀▀ █░░
█▄▄ ██▄ ▀▄▀ ██▄ █▄▄
	*/
	wstring Level = L"█   █▀▀ █ █ █▀▀ █ \n";
	Level += L"█▄▄ ██▄ ▀▄▀ ██▄ █▄▄";
	DrawString(87, 25, Level, BG_MUC + FG_MUC);

	Alphabet a;
	int y = 35;
	for (int i = 0; i < this->highScores.size(); ++i)
	{
		int x = 15;

		for (int j = 0; j < this->highScores[i].name.length(); ++j)
		{
			wstring name = L"";
			if (this->highScores[i].name[j] >= 'A' && this->highScores[i].name[j] <= 'Z')
			{
				name = a.alphabet[this->highScores[i].name[j] - 'A'];
				DrawString(x, y, name, BG + FG);
				x = x + a.SizeAlphabet[this->highScores[i].name[j] - 'A'];
			}
			if (this->highScores[i].name[j] >= '0' && this->highScores[i].name[j] <= '9')
			{
				name = a.Numbers[this->highScores[i].name[j] - '0'];
				DrawString(x, y, name, BG + FG);
				x = x + a.SizeNumbers[this->highScores[i].name[j] - '0'];
			}
		}

		int Score = this->highScores[i].point;
		wstring SCORE[5];
		int SizeScore[5];
		int z = 0;
		do
		{
			SCORE[z] = a.Numbers[Score % 10];
			SizeScore[z] = a.SizeNumbers[Score % 10];
			Score = Score / 10;
			++z;
		} while (Score > 0);
		x = 60;
		while (z > 0)
		{
			DrawString(x, y, SCORE[z - 1], BG + FG);
			x = x + SizeScore[z - 1];
			--z;
		}

		x = 95;
		DrawString(x, y, a.Numbers[this->highScores[i].level], BG + FG);
		x = x + a.SizeNumbers[this->highScores[i].level];

		y = y + 5;
		BG = BG_YELLOW;
	}
}

void Game::SaveGame(float fDeltaTime)
{
	FillRectangle(20, 20, 10, 5, L' ', BG_CYAN);
	DrawStringAlpha(22, 22, L"Save Game", BG_CYAN + FG_WHITE);
	static wstring name;
	int length = 5;

	for (char c = 'A'; c <= 'Z'; c++)
	{
		if (this->m_keys[c].bPressed && name.length() < length)
		{
			name += c;
		}
	}
	for (char c = '0'; c <= '9'; c++)
	{
		if (this->m_keys[c].bPressed && name.length() < length)
		{
			name += c;
		}
	}
	if (this->m_keys[VK_BACK].bPressed && name != L"")
	{
		name.pop_back();
	}
	if (this->m_keys[VK_RETURN].bPressed && name.length() > 0)
	{
		Save save;
		save.name = WstringToString(name);
		save.level = this->player.GetLevel();
		save.point = this->player.GetScore();
		this->loadGames.push_back(save);
		if (this->loadGames.size() > 5)
			this->loadGames.pop_front();
		SaveData("Save/LoadGames.txt", this->loadGames);

		name.clear();
		this->m_nCurrentState = 1;
		return;
	}

	DrawStringAlpha(22, 23, name, BG_CYAN + FG_WHITE);
}

void Game::DieGame(float fDeltaTime)
{
	FillRectangle(20, 20, 10, 5, L' ', BG_CYAN);
	DrawStringAlpha(22, 22, L"High score", BG_CYAN + FG_WHITE);
	static wstring name;
	int length = 5;

	for (char c = 'A'; c <= 'Z'; c++)
	{
		if (this->m_keys[c].bPressed && name.length() < length)
		{
			name += c;
		}
	}
	for (char c = '0'; c <= '9'; c++)
	{
		if (this->m_keys[c].bPressed && name.length() < length)
		{
			name += c;
		}
	}

	if (this->m_keys[VK_BACK].bPressed && name != L"")
	{
		name.pop_back();
	}
	if (this->m_keys[VK_RETURN].bPressed && name.length() > 0)
	{
		Save save;
		save.name = WstringToString(name);
		save.level = this->player.GetLevel();
		save.point = this->player.GetScore();
		this->highScores.push_back(save);
		sort(this->highScores.begin(), this->highScores.end(), cmp);
		if (this->highScores.size() > 5)
			this->highScores.pop_back();
		SaveData("Save/HighScores.txt", this->highScores);

		name.clear();
		this->m_nCurrentState = 1;
		return;
	}

	DrawStringAlpha(22, 23, name, BG_CYAN + FG_WHITE);
}

void Game::SaveData(string fileName, deque<Save> saves)
{
	ofstream file(fileName);
	for (int i = 0; i < saves.size(); i++)
	{
		file << saves[i].name << endl;
		file << saves[i].level << endl;
		file << saves[i].point << endl;
	}
	file.close();
}

void Game::LoadData(string fileName, deque<Save> &saves)
{
	ifstream file(fileName);
	if (file.fail())
	{
		return;
	}
	while (!file.eof())
	{
		string temp;
		file >> temp;
		if (temp == "")
		{
			file.close();
			return;
		}
		Save save;
		save.name = temp;
		file >> save.level;
		file >> save.point;
		saves.push_back(save);
	}
	file.close();
}