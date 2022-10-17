#include "Menu.h"

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
