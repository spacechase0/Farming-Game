#include "Game.h"
#include "ResourceManager.h"
#include<iostream>
int main()
{
	Game game;
	game.run();

	ResourceManager::unloadAll();

	return 0;
}
