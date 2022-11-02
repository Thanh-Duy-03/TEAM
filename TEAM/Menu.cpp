#include "Menu.h"

bool cmp(Save a, Save b)
{
	return (a.level > b.level || (a.level == b.level && a.point > b.point));
}

bool Game::OnUserCreate()
{
	wifstream fi("Save/Load_Game.txt");
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	fi.imbue(loc);
	for (int i = 1; i <= 5; ++i)
	{
		Save tmp;
		fi >> tmp.name;
		fi >> tmp.level;
		fi >> tmp.point;
		this->Load_Game.push_back(tmp);
	}
	fi.close();

	fi.open("Save/Die_Game.txt");
	fi.imbue(loc);
	for (int i = 1; i <= 5; ++i)
	{
		fi >> this->High_Score[i].name;
		fi >> this->High_Score[i].level;
		fi >> this->High_Score[i].point;
	}
	fi.close();
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

void Game::StartGame(float fDeltaTime, int level, int point)
{
	this->score = 200;
	this->player.x = 0;
	this->player.y = 63;
	this->player.currentLane = 0;
	this->player.LoadSprite(L"Player.txt");
	this->player.color = FG_BLUE + BG_WHITE;
	this->player.level = level;
	this->player.total = point;
	this->player.die = false;

	this->lane[0].y = 63;

	this->lane[1].x = -20;
	this->lane[1].y = 54;
	this->lane[1].LoadSprite(L"Truck.txt");
	this->lane[1].speed = 5.0f + rand() % 10;
	this->lane[1].Kc = 60 - 6 * this->player.level;
	// this->lane[1].timeToSpawn = 3 + rand() % 10;
	// this->lane[1].timeToSpawn = 7 - this->player.level;

	this->lane[2].x = 90;
	this->lane[2].y = 45;
	this->lane[2].LoadSprite(L"Truck2.txt");
	this->lane[2].speed = -10.0f;
	this->lane[2].Kc = 60 - 6 * this->player.level;
	// this->lane[2].timeToSpawn = 3 + rand() % 10;
	// this->lane[2].timeToSpawn = 8 - this->player.level;

	this->lane[3].x = -20;
	this->lane[3].y = 36;
	this->lane[3].LoadSprite(L"Truck.txt");
	this->lane[3].speed = 5.0f + rand() % 10;
	this->lane[3].Kc = 60 - 6 * this->player.level;
	// this->lane[3].timeToSpawn = 3 + rand() % 10;
	// this->lane[3].timeToSpawn = 10 - this->player.level;

	this->lane[4].x = -20;
	this->lane[4].y = 27;
	this->lane[4].LoadSprite(L"Truck.txt");
	this->lane[4].speed = 5.0f + rand() % 10;
	this->lane[4].Kc = 60 - 6 * this->player.level;
	// this->lane[4].timeToSpawn = 3 + rand() % 10;
	// this->lane[4].timeToSpawn = 8 - this->player.level;

	this->lane[5].x = -20;
	this->lane[5].y = 18;
	this->lane[5].LoadSprite(L"Truck.txt");
	this->lane[5].speed = 5.0f + rand() % 10;
	this->lane[5].Kc = 60 - 6 * this->player.level;
	// this->lane[5].timeToSpawn = 3 + rand() % 10;
	// this->lane[5].timeToSpawn = 10 - this->player.level;

	this->lane[6].x = -20;
	this->lane[6].y = 9;
	this->lane[6].LoadSprite(L"Truck.txt");
	this->lane[6].speed = 5.0f + rand() % 10;
	this->lane[6].Kc = 60 - 6 * this->player.level;
	// this->lane[6].timeToSpawn = 5 + rand() % 10;
	// this->lane[6].timeToSpawn = 7 - this->player.level;

	this->lane[7].y = 0;
	this->m_nCurrentState = 6;
}

void Game::PlayGame(float fDeltaTime)
{
	static float time = 0.0;
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_WHITE);
	Fill(0, 0, 89, 7, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);
	DrawLine(0, 8, 89, 8, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	for (int i = 1; i <= 5; ++i)
	{
		DrawLine(0, 8 + 9 * i, 89, 8 + 9 * i, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	}
	DrawLine(0, 62, 89, 62, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	Fill(0, 63, 89, 69, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);
	DrawStringAlpha(this->player.x, this->player.y, this->player.sprite, this->player.color);
	DrawLanes();
	DrawRectangle(90, 0, 30, this->m_nScreenHeight, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	FillRectangle(91, 1, 28, this->m_nScreenHeight - 2, PIXEL_SOLID, FG_WHITE + BG_WHITE);

	DrawScore(fDeltaTime);
	if (this->player.currentLane != 0 && this->player.currentLane != 7)
	{
		for (int i = 0; i < this->lane[this->player.currentLane].posList.size(); i++)
		{
			if (this->player.x <= this->lane[this->player.currentLane].posList[i] + (float)this->lane[this->player.currentLane].width && this->player.x >= this->lane[this->player.currentLane].posList[i] - this->player.width)
			{
				this->player.die = true;
			}
		}
	}
	// Qua mang choi

	if (this->player.currentLane == 7)
	{
		this->player.level++;
		this->player.total += (int)this->score;
		StartGame(fDeltaTime, this->player.level, this->player.total);
	}
	if (!this->player.die)
	{
		UpdateLane(fDeltaTime);
		if (this->m_keys['L'].bPressed)
		{
			this->m_nCurrentState = 7;
		}
		if (this->m_keys[VK_ESCAPE].bPressed)
		{
			this->m_nCurrentState = 1;
		}
		if ((this->m_keys['A'].bPressed || this->m_keys[VK_LEFT].bPressed) && this->player.x - 5 >= 0)
		{
			this->player.x -= 5;
		}
		if ((this->m_keys['D'].bPressed || this->m_keys[VK_RIGHT].bPressed) && this->player.x + this->player.width + 5 <= 89)
		{
			this->player.x += 5;
		}
		if ((this->m_keys['W'].bPressed || this->m_keys[VK_UP].bPressed) && this->player.currentLane < 7)
		{
			this->player.currentLane++;
			this->player.y = this->lane[this->player.currentLane].y;
		}
		if ((this->m_keys['S'].bPressed || this->m_keys[VK_DOWN].bPressed) && this->player.currentLane > 0)
		{
			this->player.currentLane--;
			this->player.y = this->lane[this->player.currentLane].y;
		}
	}
	else
	{
		time += fDeltaTime;
		effect(time);
		if (time >= 3.0)
		{
			time = 0;
			this->m_nCurrentState = 8;
			return;
		}
	}
}

void Game::LoadGame(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
		return;
	}
	int vtLoadGame = 0;
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
		StartGame(fDeltaTime, this->Load_Game[vtLoadGame].level, this->Load_Game[vtLoadGame].point);
	}
	// Thêm danh sách load game
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
	DrawStringAlpha(10, 9, L"Save Game", BG_CYAN + FG_WHITE);
	static wstring name;

	for (char c = 'A'; c <= 'Z'; c++)
	{
		if (this->m_keys[c].bPressed)
		{
			name += c;
		}
	}
	for (char c = '0'; c <= '9'; c++)
	{
		if (this->m_keys[c].bPressed)
		{
			name += c;
		}
	}
	if (this->m_keys[VK_SPACE].bPressed)
	{
		name += L' ';
	}
	if (this->m_keys[VK_BACK].bPressed && name != L"")
	{
		name.pop_back();
	}
	if (this->m_keys[VK_RETURN].bPressed)
	{
		this->m_nCurrentState = 1;
		name.clear();
		return;
	}

	DrawStringAlpha(10, 10, name, BG_CYAN + FG_WHITE);
}

void Game::UpdateLane(float fDeltaTime)
{
	for (int i = 0; i < 8; i++)
	{
		this->lane[i].Update(fDeltaTime, this->m_nScreenWidth);
	}
}
void Game::DrawLanes()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < this->lane[i].posList.size(); j++)
		{
			if (i < 7 && i > 0)
			{
				// ((ran == this->lane[i].y) ? Draw(5, this->lane[i].y, PIXEL_SOLID, BG_RED + FG_RED) : Draw(5, this->lane[i].y, PIXEL_SOLID, FG_GREEN + BG_GREEN));
				if (this->lane[i].stop)
				{
					Draw(5, this->lane[i].y, PIXEL_SOLID, BG_RED + FG_RED);
				}
				else
				{
					Draw(5, this->lane[i].y, PIXEL_SOLID, BG_GREEN + FG_GREEN);
				}
			}
			DrawString((int)this->lane[i].posList[j], this->lane[i].y, this->lane[i].sprite, this->lane[i].color);
		}
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
	this->score -= (fDeltaTime * 1.5);
	int k = this->score;
	for (int i = 1; i <= 3; i++)
	{

		DrawString(112 - 5 * i, 12, Numbers[k % 10], BG_WHITE + FG_BLUE);
		k /= 10;
	}

	int j = this->player.total;
	for (int i = 1; i <= 3; i++)
	{

		DrawString(112 - 5 * i, 19, Numbers[j % 10], BG_WHITE + FG_BLUE);
		j /= 10;
	}
	DrawString(112 - 5, 25, Numbers[this->player.level], BG_WHITE + FG_BLUE);

	if (this->score <= 0)
	{
		this->m_nCurrentState = 1;
	}
	/*	█▀▀█   ▄█░   █▀█   █▀▀█   ░█▀█░   █▀▀   ▄▀▀▄   ▀▀▀█   ▄▀▀▄   ▄▀▀▄
		█▄▀█   ░█░   ░▄▀   ░░▀▄   █▄▄█▄   ▀▀▄   █▄▄░   ░░█░   ▄▀▀▄   ▀▄▄█
		█▄▄█   ▄█▄   █▄▄   █▄▄█   ░░░█░   ▄▄▀   ▀▄▄▀   ░▐▌░   ▀▄▄▀   ░▄▄▀*/
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
	if (this->m_keys[VK_RETURN].bPressed)
	{
		this->Load_Game.pop_front();
		Save tmp;
		tmp.name = name;
		tmp.level = this->player.level;
		tmp.point = this->player.total;
		this->Load_Game.push_back(tmp);

		wofstream fo("Save/Load_Game.txt");
		locale loc(locale(), new codecvt_utf8<wchar_t>);
		fo.imbue(loc);
		for (int i = 0; i < this->Load_Game.size(); ++i)
		{
			fo << this->Load_Game[i].name << "\n";
			fo << this->Load_Game[i].level << "\n";
			fo << this->Load_Game[i].point << "\n";
		}
		fo.close();
		name.clear();
		this->m_nCurrentState = 1;
		return;
	}

	DrawStringAlpha(22, 23, name, BG_CYAN + FG_WHITE);
}

void Game::DieGame(float fDeltaTime)
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
	if (this->m_keys[VK_RETURN].bPressed)
	{
		this->High_Score[6].name = name;
		this->High_Score[6].level = this->player.level;
		this->High_Score[6].point = this->player.total;
		sort(this->High_Score + 1, this->High_Score + 6 + 1, cmp);

		locale loc(locale(), new codecvt_utf8<wchar_t>);
		wofstream fo("Save/Die_Game.txt");
		fo.imbue(loc);
		for (int i = 1; i <= 5; ++i)
		{
			fo << this->High_Score[i].name << "\n";
			fo << this->High_Score[i].level << "\n";
			fo << this->High_Score[i].point << "\n";
		}
		fo.close();
		name.clear();
		this->m_nCurrentState = 1;
		return;
	}

	DrawStringAlpha(22, 23, name, BG_CYAN + FG_WHITE);
}

void Game::effect(float time)
{
	if (time < 0.5)
	{
		this->player.color = FG_RED + BG_WHITE;
		this->player.LoadSprite(L"firstGlow.txt");
	}
	else if (time < 1)
		this->player.LoadSprite(L"secondGlow.txt");
	else if (time < 1.5)
		this->player.LoadSprite(L"thirdGlow.txt");
}