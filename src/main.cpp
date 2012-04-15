#include "Game.h"
#include "ResourceManager.h"
#include<iostream>
int main()
{std::cout<"Hi Kake\n";
	Game game;
	game.run();

	ResourceManager::unloadAll();

	{
	    std::cout << "Hai space" << std::endl;
	}

	return 0;
}
