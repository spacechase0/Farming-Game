#include "Game.h"
#include "ResourceManager.h"
#include<iostream>
int main()
{std::cout<"Hi Kake\n";
	Game game;
	game.run();
	
	ResourceManager::unloadAll();
	
	return 0;
}
