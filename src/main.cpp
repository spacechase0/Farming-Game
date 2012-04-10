#include "Game.h"
#include "ResourceManager.h"

int main()
{
	Game game;
	game.run();
	
	ResourceManager::unloadAll();
	
	return 0;
}
