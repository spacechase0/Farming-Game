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

#define ValidateLoop(a) \
		if ( std::distance( a.begin(), it ) >= static_cast< int >( a.size() ) ) \
		{          \
			break; \
		}          \
		if ( !( * it ) ) \
		{             \
			continue; \
		}             \

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
	if ( layers.size() > 0 )
	{
		CreateTestObject();

		cameraController = new obj::CameraController( ( * this ), game.window );
		gameObjects.push_back( ObjectPtr( cameraController ) );

		simulateWorld = true;
	}
}

void SceneGame::Terminate()
{
	layers.clear();
	gameObjects.clear();
	menuObjects.clear();
	garbageObjects.clear();
	itemDefs.clear();

	player = NULL;
	cameraController = NULL;
}

void SceneGame::Update( sf::RenderWindow& window )
{
	std::list< boost::shared_ptr< obj::Base > >& container = simulateWorld ? gameObjects : menuObjects;
	for ( auto it = container.begin(); it != container.end(); ++it )
	{
		ValidateLoop( container );
		( * it )->Update();
	}
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

	std::list< boost::shared_ptr< obj::Base > >& container = simulateWorld ? gameObjects : menuObjects;
	for ( auto it = container.begin(); it != container.end(); ++it )
	{
		ValidateLoop( container );
		( * it )->Update( event );
	}
}

void SceneGame::Draw( sf::RenderWindow& window )
{
	window.Clear( sf::Color::Black );

	for ( auto it = layers.begin(); it != layers.end(); ++it )
	{
		TileLayer& layer = ( * it );
		DrawLayer( window, layer );
	}
	{
		using namespace std::placeholders;
		auto compare = std::bind( &SceneGame::CompareObjects, this, _1, _2 );
		gameObjects.sort( compare );

		for ( auto it = gameObjects.begin(); it != gameObjects.end(); ++it )
		{
			ValidateLoop( gameObjects );
			( * it )->Draw( window );
		}
	}
	{
		// We want the GUI to have a static position on the screen
		sf::View oldView = window.GetView();
		sf::View newView( sf::Vector2f( Game::WindowSize.x / 2, Game::WindowSize.y / 2 ), sf::Vector2f( Game::WindowSize ) );
		window.SetView( newView );
		
		for ( auto it = menuObjects.begin(); it != menuObjects.end(); ++it )
		{
			ValidateLoop( menuObjects );
			( * it )->Draw( window );
		}
		
		window.SetView( oldView );
	}

	window.Display();

	// Don't ask why I do it here instead of Update
	for ( auto it = garbageObjects.begin(); it != garbageObjects.end(); ++it )
	{
		if ( it->second == GarbageType::GameGarbage )
		{
			gameObjects.erase( it->first );
		}
		else if ( it->second == GarbageType::MenuGarbage )
		{
			menuObjects.erase( it->first );
		}
	}
	garbageObjects.clear();
}


bool SceneGame::IsTileEmpty( int x, int y, int layer )
{
	if ( layer <= -1 )
	{
		for ( auto it = layers.begin(); it != layers.end(); ++it )
		{
			if ( x < 0 or x >= static_cast< int >( it->GetTiles().size() ) or
				 y < 0 or y >= static_cast< int >( ( * it )[ x ].size() ) )
			{
				return false;
			}

			bool solid = ( * it )[ x ][ y ].GetCollision();
			if ( solid )
			{
				return true;
			}
		}
		return false;
	}
	else if ( static_cast< unsigned int >( layer ) >= layers.size() )
	{
		return false;
	}
	else
	{
		return layers[ layer ][ x ][ y ].GetCollision();
	}
}

bool SceneGame::IsTileEmpty( sf::Vector2i pos, int layer )
{
	return IsTileEmpty( pos.x, pos.y, layer );
}

void SceneGame::CreateChatDialog( const std::vector< std::string >& messages )
{
	sf::Texture& background = game.GetTexture( "dialogs/chat-base.png" );
	sf::Texture& button = game.GetTexture( "dialogs/chat-button.png" );
	sf::Font& font = game.GetFont( "fonts/Grantham/Grantham Bold.ttf" );

	obj::Base* chat = new obj::DialogChat( ( * this ), background, button, font, messages );
	menuObjects.push_back( boost::shared_ptr< obj::Base >( chat ) );

	simulateWorld = false;
}

void SceneGame::LoadMap( const std::string& map )
{
	MapLoader loader( game, ( * this ), layers, gameObjects );
	if ( !loader.LoadMap( map ) )
	{
		std::vector< std::string > str;
		str.push_back( "Map '" + map + "'failed to load." );
		CreateChatDialog( str );
	}
}

void SceneGame::CreateTestObject()
{
	sf::Texture& texture = game.GetTexture( "characters/player.png" );
	player = new obj::Player( ( * this ), texture, sf::Vector2f( 13 * Game::TileSize, 5 * Game::TileSize ) );

	gameObjects.push_back( boost::shared_ptr< obj::Base >( player ) );
}

void SceneGame::DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const
{
	sf::Texture& texture = game.GetTexture( "tiles/outside.png" );
	sf::Sprite spr( texture );

	for ( size_t ix = 0; ix < layer.GetTiles().size(); ++ix )
	{
		for ( size_t iy = 0; iy < layer.GetTiles()[ ix ].size(); ++iy )
		{
			const Tile& tile = layer.GetTile( ix, iy );
			sf::Uint8 index = tile.GetIndex();

			sf::Vector2i texturePos( ( index % 16 ) * Game::TileSize, ( index / 16 ) * Game::TileSize );
			spr.SetSubRect( sf::IntRect( texturePos.x, texturePos.y, Game::TileSize, Game::TileSize ) );
			spr.SetPosition( ix * 32, iy * 32 );

			window.Draw( spr );
		}
	}
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

bool SceneGame::CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 )
{
	if ( !util::IsOfType< obj::RenderObject* >( obj1.get() ) or !util::IsOfType< obj::RenderObject* >( obj2.get() ) )
	{
		return false;
	}

	obj::RenderObject* firstObj = static_cast< obj::RenderObject* >( &( * obj1 ) );
	obj::RenderObject* secondObj = static_cast< obj::RenderObject* >( &( * obj2 ) );

	return ( -firstObj->GetPosition().y ) > ( -secondObj->GetPosition().y );
}
