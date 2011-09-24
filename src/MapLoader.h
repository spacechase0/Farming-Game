#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <xml/Xml.h>
#include "TileLayer.h"
#include "scenes/SceneGame.h"

class Game;

class MapLoader
{
	public:
		MapLoader( Game& theGame, SceneGame& theScene, std::vector< TileLayer >& theLayers, MapManager::ObjectList& theObjects );
		
		bool LoadMap( const std::string& mapName );
	
	private:
		Game& game;
		SceneGame& scene;
		std::vector< TileLayer >& layers;
		MapManager::ObjectList& objects;
		size_t width, height;
		
		bool LoadXml( xml::Document& doc, const std::string& mapName );
		
		bool ParseTileLayer( xml::Node& node );
		std::vector< Tile > LoadTileTypes( sf::Texture& tex, const std::string& name );
		
		bool ParseStaticObjects( xml::Node& node );
		bool ParseSceneryObject( xml::Node& node );
		bool ParseEntranceObject( xml::Node& node );
};

#endif // MAPLOADER_H
