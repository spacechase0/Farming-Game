#include "Game.h"
#include "ResourceManager.h"

int main()
{
	Game game;
	game.run();

	ResourceManager::unloadAll();

	{
	    std::cout << "Hai space" << std::endl;
	}

	return 0;
}
