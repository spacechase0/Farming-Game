#include "scenes/SceneGame.h"

#include <typeinfo>
#include <fstream>
#include <algorithm>

#include "Game.h"
#include "obj/Objects.h"
#include <xml/Xml.h>
#include "util/Convert.h"
#include "MapLoader.h"
#include "util/Type.h"

SceneGame::SceneGame( Game& game )
   : SceneBase::SceneBase( game )
{
}

void SceneGame::Initialize()
{
	LoadItems( "food.xml" );
	LoadItems( "seeds.xml" );
	LoadItems( "tools.xml" );
	LoadItems( "misc.xml" );

	LoadMap( "testing" );
	maps.currentMap = "testing";
	if ( maps.maps.size() > 0 )
	{
		CreateTestObject();

		cameraController = new obj::CameraController( ( * this ), game.window );

		simulateWorld = true;
	}
}

void SceneGame::Terminate()
{
	maps = MapManager();
	itemDefs.clear();

	player = NULL;
	cameraController = NULL;
}

void SceneGame::Update( sf::RenderWindow& window )
{
	maps.Update();
}

void SceneGame::Update( sf::RenderWindow& window, const sf::Event& event )
{
	if ( event.Type == sf::Event::Closed )
	{
		window.Close();
	}

	if ( event.Type == sf::Event::KeyPressed )
	{
		if( event.Key.Code == sf::Keyboard::Escape )
		{
			game.ChangeScene( "MainMenu" );
		}
	}
	
	maps.Update( event );
}

void SceneGame::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );
	
	cameraController->Draw( window );
	maps.Draw( window );

	window.Display();
	
	maps.CollectGarbage();
}


bool SceneGame::IsTileEmpty( MapManager::Map& map, int x, int y )
{
	for ( auto it = map.layers.begin(); it != map.layers.end(); ++it )
	{
		if ( x < 0 or x >= static_cast< int >( it->GetTiles().size() ) or
			 y < 0 or y >= static_cast< int >( ( * it )[ x ].size() ) )
		{
			break;
		}

		bool solid = ( * it )[ x ][ y ].GetCollision();
		if ( solid )
		{
			return true;
		}
	}
	
	for ( auto it = map.objects.begin(); it != map.objects.end(); ++it )
	{
		if ( !util::IsOfType< obj::RenderObject* >( it->get() ) )
		{
			continue;
		}
		
		obj::RenderObject* object = static_cast< obj::RenderObject* >( it->get() );
		if ( !object->CanCollide() )
		{
			continue;
		}
		
		if ( object->GetCollisionRect().Contains( x * Game::TileSize, y * Game::TileSize ) )
		{
			return false;
		}
	}
	
	return true;
}

bool SceneGame::IsTileEmpty( MapManager::Map& map, sf::Vector2i pos )
{
	return IsTileEmpty( map, pos.x, pos.y );
}

void SceneGame::CreateChatDialog( const std::vector< std::string >& messages )
{
	sf::Texture& background = game.GetTexture( "dialogs/chat-base.png" );
	sf::Texture& button = game.GetTexture( "dialogs/chat-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );

	obj::Base* chat = new obj::DialogChat( ( * this ), background, button, font, messages );
	maps.menuObjects.push_back( boost::shared_ptr< obj::Base >( chat ) );

	simulateWorld = false;
}

void SceneGame::LoadMap( const std::string& mapName )
{
	maps.maps.insert( std::make_pair( mapName, MapManager::MapPtr( new MapManager::Map ) ) );
	MapManager::Map& map = ( * maps[ mapName ] );
	
	MapLoader loader( game, ( * this ), map.layers, map.objects );
	if ( !loader.LoadMap( mapName ) )
	{
		std::vector< std::string > str;
		str.push_back( "Map '" + mapName + "'failed to load." );
		CreateChatDialog( str );
		maps.maps.erase( maps.maps.find( mapName ) );
	}
}

void SceneGame::CreateTestObject()
{
	sf::Texture& texture = game.GetTexture( "characters/player.png" );
	player = new obj::Player( ( * this ), ( * maps[ maps.currentMap ] ), texture, sf::Vector2f( 13 * Game::TileSize, 5 * Game::TileSize ) );

	maps[ maps.currentMap ]->objects.push_back( boost::shared_ptr< obj::Base >( player ) );
}

void SceneGame::LoadItems( const std::string& filename )
{
	std::fstream file( ( "res/items/" + filename ).c_str(), std::fstream::in );
	if ( !file )
	{
		std::cout << "Failed to load '" << file << "'." << std::endl;
		return;
	}

	std::string contents;
	while ( true )
	{
		std::string line;
		std::getline( file, line );
		if ( !file.eof() )
		{
			contents += line;
		}
		else
		{
			break;
		}
	}

	xml::Document doc;
	auto status = doc.Parse( contents );
	if ( !std::get< 0 >( status ) )
	{
		std::cout << "Failed to parse '" << file << "': " << std::get< 1 >( status ) << std::endl;
		return;
	}

	auto children = doc.GetRootNode().GetChildren();
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * ( * it ) );
		std::string name = xml::GetAttribute( node, "name" ).GetValue();
		std::string desc = xml::GetAttribute( node, "desc" ).GetValue();
		std::string indexStr = xml::GetAttribute( node, "index" ).GetValue();
		std::string typeStr = xml::GetAttribute( node, "type" ).GetValue();

		item::Item::Type type = ToType( typeStr );
		size_t index = util::FromString< size_t >( indexStr );

		item::Item* item;
		switch ( type )
		{
			using namespace item;

			case Item::Type::Food:
				{
					std::string priceStr = xml::GetAttribute( node, "price" ).GetValue();
					size_t price = util::FromString< size_t >( priceStr );

					item = new Food( name, desc, index, price );
				}
				break;

			case Item::Type::Meal:
				{
					std::string priceStr = xml::GetAttribute( node, "price" ).GetValue();
					size_t price = util::FromString< size_t >( priceStr );

					item = new Food( name, desc, index, price );
					#warning TO DO: Make a class for Meal (since they have a seperate item file)
				}
				break;

			case Item::Type::Seed:
				{
					std::string crop = xml::GetAttribute( node, "crop" ).GetValue();
					item = new Seed( name, desc, index, crop );
				}
				break;

			case Item::Type::Tool:
				{
					std::string actionStr = xml::GetAttribute( node, "action" ).GetValue();
					std::string breakChanceStr = xml::GetAttribute( node, "breakchance" ).GetValue();

					Tool::Action action = ToAction( actionStr );
					float breakChance = util::FromString< float >( breakChanceStr );

					item = new Tool( name, desc, index, action, breakChance );
				}
				break;

			case Item::Type::Misc:
				{
					item = new Item( name, desc, index );
				}
				break;
		};
		itemDefs.insert( std::make_pair( name, boost::shared_ptr< item::Item >( item ) ) );
	}
}

item::Item::Type SceneGame::ToType( const std::string& str )
{
	using item::Item;
	if ( str == "food" )
	{
		return Item::Type::Food;
	}
	else if ( str == "meal" )
	{
		return Item::Type::Meal;
	}
	else if ( str == "seed" )
	{
		return Item::Type::Seed;
	}
	else if ( str == "tool" )
	{
		return Item::Type::Tool;
	}

	return Item::Type::Misc;
}

item::Tool::Action SceneGame::ToAction( const std::string& str )
{
	using item::Tool;
	if ( str == "dig" )
	{
		return Tool::Action::Dig;
	}
	else if ( str == "chop" )
	{
		return Tool::Action::Chop;
	}
	else if ( str == "fish" )
	{
		return Tool::Action::Fish;
	}

	return Tool::Action::None;
}
