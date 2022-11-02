#include "Menu.h"

int main()
{
	srand(time(NULL));
	Game game;
	int size = 2;
	while (game.ConstructConsole(120, 70, size, size) == 0)
	{
		size++;
	}
	size -= 1;
	game.ConstructConsole(120, 70, size, size);
	game.ChangeName(L"Game");
	game.Start();
	return 0;
}
