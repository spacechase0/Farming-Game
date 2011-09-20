#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <xml/Xml.h>
#include "TileLayer.h"
#include "scenes/SceneGame.h"

class Game;

class MapLoader
{
	public:
		MapLoader( Game& theGame, std::vector< TileLayer >& theLayers, SceneGame::ObjectList& theObjects );
		
		bool LoadMap( const std::string& mapName );
	
	private:
		Game& game;
		std::vector< TileLayer >& layers;
		SceneGame::ObjectList& objects;
		size_t width, height;
		
		bool LoadXml( xml::Document& doc, const std::string& mapName );
		bool ParseTileLayer( xml::Node& node );
		std::vector< Tile > LoadTileTypes( sf::Texture& tex, const std::string& name );
};

#endif // MAPLOADER_H
