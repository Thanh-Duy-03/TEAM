#include "Menu.h"

int main()
{
	srand(time(0));
	Game game;
	if (!game.ConstructConsole(120,70, 9, 9))
	{
		game.ChangeName(L"Game");
		game.Start();
	}
	return 0;
}
