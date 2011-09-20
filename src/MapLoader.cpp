#include "MapLoader.h"

#include <algorithm>
#include <fstream>

#include "Game.h"
#include "util/Convert.h"
#include "util/Tokenize.h"
#include "obj/Objects.h"

MapLoader::MapLoader( Game& theGame, SceneGame& theScene, std::vector< TileLayer >& theLayers, SceneGame::ObjectList& theObjects )
   : game( theGame ),
     scene( theScene ),
     layers( theLayers ),
     objects( theObjects )
{
}

bool MapLoader::LoadMap( const std::string& mapName )
{
	xml::Document doc;
	if ( !LoadXml( doc, "res/maps/" + mapName + ".xml" ) )
	{
		return false;
	}

	xml::Node& root = doc.GetRootNode();

	std::string widthStr = xml::GetAttribute( root, "width" ).GetValue();
	std::string heightStr = xml::GetAttribute( root, "height" ).GetValue();

	width = util::FromString< size_t >( widthStr );
	height = util::FromString< size_t >( heightStr );

	auto children = root.GetChildren();
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * it->get() );
		if ( node.GetName() == "TileLayer" )
		{
			if ( !ParseTileLayer( node ) )
			{
				return false;
			}
		}
		else if ( node.GetName() == "StaticObjects" )
		{
			if ( !ParseStaticObjects( node ) )
			{
				return false;
			}
		}
	}

	return true;
}

bool MapLoader::LoadXml( xml::Document& doc, const std::string& filename )
{
	std::fstream file( filename.c_str(), std::fstream::in );
	if ( !file )
	{
		return false;
	}

	std::string contents;
	while ( true )
	{
		std::string line;
		std::getline( file, line );

		if ( file.eof() )
		{
			break;
		}

		contents += line;
	}

	return std::get< 0 >( doc.Parse( contents ) );
}

bool MapLoader::ParseTileLayer( xml::Node& node )
{
	std::string tileset = xml::GetAttribute( node, "tileset" ).GetValue();
	sf::Texture& tex = game.GetTexture( "tiles/" + tileset + ".png" );
	std::vector< Tile > tileTypes = LoadTileTypes( tex, tileset );
	if ( tileTypes.size() <= 0 )
	{
		return false;
	}

	std::vector< std::string > tileData;

	auto children = node.GetChildren();
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * it->get() );
		if ( !node.IsTextNode() )
		{
			continue;
		}

		std::vector< std::string > tokens = util::Tokenize( node.GetText(), " " );
		tileData.insert( tileData.end(), tokens.begin(), tokens.end() );
	}

	if ( tileData.size() < width * height )
	{
		return false;
	}

	TileLayer layer( sf::Vector2i( width, height ), tileTypes[ 0 ] );
	for ( auto it = tileData.begin(); it != tileData.end(); ++it )
	{
		size_t dist = std::distance( tileData.begin(), it );
		size_t row = dist / width;
		size_t col = dist % width;

		if ( row >= height )
		{
			break;
		}

		sf::Uint8 index = util::FromString< sf::Uint16 >( * it ); // 16 instead of 8 because 8 is really a char...
		layer[ col ][ row ] = tileTypes[ index ];
	}
	layers.push_back( layer );

	return true;
}

std::vector< Tile > MapLoader::LoadTileTypes( sf::Texture& tex, const std::string& name )
{
	xml::Document doc;
	if ( !LoadXml( doc, "res/tiles/" + name + ".xml" ) )
	{
		return std::vector< Tile >();
	}

	auto children = doc.GetRootNode().GetChildren();
	std::vector< Tile > tiles( 256 );
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * it->get() );
		if ( node.GetName() != "Type" )
		{
			continue;
		}

		std::string indexStr = xml::GetAttribute( node, "index" ).GetValue();
		std::string collideStr = xml::GetAttribute( node, "collide" ).GetValue();

		sf::Uint8 index = util::FromString< sf::Uint16 >( indexStr ); // 16 instead of 8 because 8 is really a char...
		bool collide = util::FromString< bool >( collideStr );

		tiles[ index ] = Tile( tex, index, collide );
	}

	return tiles;
}

bool MapLoader::ParseStaticObjects( xml::Node& node )
{
	auto children = node.GetChildren();
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * it->get() );
		if ( node.GetName() == "Scenery" )
		{
			if ( !ParseSceneryObject( node ) )
			{
				return false;
			}
		}
	}

	return true;
}

bool MapLoader::ParseSceneryObject( xml::Node& node )
{
	sf::Texture& tex = game.GetTexture( "scenery/" + xml::GetAttribute( node, "file" ).GetValue() + ".png" );
	std::string xStr = xml::GetAttribute( node, "x" ).GetValue();
	std::string yStr = xml::GetAttribute( node, "y" ).GetValue();

	float x = util::FromString< float >( xStr );
	float y = util::FromString< float >( yStr );

	sf::Vector2f pos( x * Game::TileSize, y * Game::TileSize );

	boost::shared_ptr< obj::Base > scenery( new obj::RenderObject( scene, tex, pos ) );
	objects.push_back( scenery );

	return true;
}
