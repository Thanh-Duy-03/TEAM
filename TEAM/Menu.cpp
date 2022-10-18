#include "Menu.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->currentLane = 0;
	this->width = 0;
	this->sprite = L"";
	this->color = FG_BLACK + BG_WHITE;
	this->die = false;
}

void Player::LoadSprite(wstring fileName)
{
	wfstream file(fileName);
	this->sprite = L"";
	if (file.is_open())
	{
		locale loc(locale(), new codecvt_utf8<wchar_t>);
		file.imbue(loc);
		wstring line;
		while (!file.eof())
		{
			getline(file, line);
			this->sprite += line + L"\n";
		}
	}
	file.close();
}

Lane::Lane()
{
	this->speed = 0;
	this->sprite = L"";
	this->time = 0;
	this->timeToSpawn = 0;
	this->color = FG_BLACK + BG_WHITE;
	this->y = 0;
	this->stop = false;
	this->timeToStop = 4;
}

void Lane::LoadSprite(wstring fileName)
{
	wfstream file(fileName);
	this->sprite = L"";
	if (file.is_open())
	{
		locale loc(locale(), new codecvt_utf8<wchar_t>);
		file.imbue(loc);
		wstring line;
		int maxWidth = 0;
		while (!file.eof())
		{
			getline(file, line);
			if (maxWidth < line.size())
				maxWidth = line.size();
			this->sprite += line + L"\n";
		}
		this->width = maxWidth;
	}
	file.close();
}
int ran = 9;
void Lane::Update(float fDeltaTime, int screenWidth)
{
	
	if (this->stop &&this->y==ran )
	{
		timeStop += fDeltaTime;
		if (this->timeStop >= this->timeToStop)
		{
			this->timeStop = 0;
			this->stop = false;
		}
		return;
	}
	this->timeStop += fDeltaTime;
	if (this->timeStop >= this->timeToStop )
	{
		this->stop = true;
		 ran = 9 * (rand() % 6 + 1);
		this->timeStop = 0;
	}

	this->time += fDeltaTime;
	if (this->posList.empty() || this->time >= this->timeToSpawn)
	{
		float newPos = 0;
		this->posList.push_back(newPos);
		this->time = 0;
	}
	else
	{
		for (int i = 0; i < this->posList.size(); i++)
		{
			this->posList[i] += this->speed * fDeltaTime;
			if (this->posList[i] >= screenWidth || this->posList[i] < 0)
			{
				this->posList.pop_front();
			}
		}
	}
}

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
	case 0: // Exit
		return false;

	case 1: // Menu
		StartMenu(fDeltaTime);
		break;
	case 2: // New Game
		StartGame(fDeltaTime, 1);
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

void Game::StartGame(float fDeltaTime, int level)
{
	this->player.x = 0;
	this->player.y = 63;
	this->player.currentLane = 0;
	this->player.LoadSprite(L"Player.txt");
	this->player.color = FG_BLUE + BG_WHITE;

	this->lane[0].y = 63;

	this->lane[1].y = 54;
	this->lane[1].LoadSprite(L"Truck.txt");
	this->lane[1].speed = 5.0f + rand() % 10;
	this->lane[1].timeToSpawn = 3 + rand() % 10;

	this->lane[2].y = 45;
	this->lane[2].LoadSprite(L"Truck.txt");
	this->lane[2].speed = 10.0f;
	this->lane[2].timeToSpawn = 3 + rand() % 10;

	this->lane[3].y = 36;
	this->lane[3].LoadSprite(L"Truck.txt");
	this->lane[3].speed = 5.0f + rand() % 10;
	this->lane[3].timeToSpawn = 3 + rand() % 10;

	this->lane[4].y = 27;
	this->lane[4].LoadSprite(L"Truck.txt");
	this->lane[4].speed = 5.0f + rand() % 10;
	this->lane[4].timeToSpawn = 3 + rand() % 10;

	this->lane[5].y = 18;
	this->lane[5].LoadSprite(L"Truck.txt");
	this->lane[5].speed = 5.0f + rand() % 10;
	this->lane[5].timeToSpawn = 3 + rand() % 10;

	this->lane[6].y = 9;
	this->lane[6].LoadSprite(L"Truck.txt");
	this->lane[6].speed = 5.0f + rand() % 10;
	this->lane[6].timeToSpawn = 5 + rand() % 10;

	this->lane[7].y = 0;
	this->m_nCurrentState = 6;
}

void Game::PlayGame(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_WHITE);
	Fill(0, 0, 89, 7, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);
	DrawLine(0, 8, 89, 8, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	for (int i = 1; i <= 5; ++i)
		DrawLine(0, 8 + 9 * i, 89, 8 + 9 * i, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	DrawLine(0, 62, 89, 62, PIXEL_SOLID, FG_BLACK + BG_WHITE);
	Fill(0, 63, 89, 69, PIXEL_QUARTER, FG_DARK_GREY + BG_BLACK);
	DrawStringAlpha(this->player.x, this->player.y, this->player.sprite, this->player.color);
	DrawLane();
	DrawRectangle(90, 0, 30, this->m_nScreenHeight, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	FillRectangle(91, 1, 28, this->m_nScreenHeight - 2, PIXEL_SOLID, FG_WHITE + BG_WHITE);

	UpdateLane(fDeltaTime);
	if (this->player.currentLane != 0 && this->player.currentLane != 7)
	{
		for (int i = 0; i < this->lane[this->player.currentLane].posList.size(); i++)
		{
			if (this->player.x <= this->lane[this->player.currentLane].posList[i] + (float)this->lane[this->player.currentLane].width && this->player.x >= this->lane[this->player.currentLane].posList[i])
			{
				this->m_nCurrentState = 1;
			}
			
		}
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

void Game::LoadGame(float fDeltaTime)
{
	FillRectangle(0, 0, this->m_nScreenWidth, this->m_nScreenHeight, L' ', BG_CYAN);
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
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
	if (this->m_keys[VK_ESCAPE].bPressed)
	{
		this->m_nCurrentState = 1;
	}
}

void Game::UpdateLane(float fDeltaTime)
{
	for (int i = 0; i < 8; i++)
	{
		this->lane[i].Update(fDeltaTime, this->m_nScreenWidth);
	}
}
void Game::DrawLane()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < this->lane[i].posList.size(); j++)
		{
			DrawString((int)this->lane[i].posList[j], this->lane[i].y, this->lane[i].sprite, this->lane[i].color);
		}
	}
}