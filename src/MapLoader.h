#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "TileLayer.h"
#include "scenes/SceneGame.h"

class MapLoader
{
	public:
		MapLoader( std::vector< TileLayer >& layers, SceneGame::ObjectList& objects );
		
		bool LoadFromFile( const std::string& mapName );
	
	private:
		std::vector< TileLayer >& layers;
		SceneGame::ObjectList& objects;
		
};

#endif // MAPLOADER_H
