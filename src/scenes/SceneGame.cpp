#include "scenes/SceneGame.h"

#include <typeinfo>
#include <fstream>
#include <algorithm>

#include "Game.h"
#include "obj/Objects.h"
#include <xml/Xml.h>
#include "util/Convert.h"

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
	
	CreateTestLayer();
	CreateTestObject();
	
	auto cc = new obj::CameraController( ( * this ), game.window );
	cameraController = boost::shared_ptr< obj::CameraController >( cc );
	gameObjects.push_back( ObjectPtr( cameraController.get() ) );
	
	simulateWorld = true;
}

void SceneGame::Terminate()
{
	itemDefs.clear();
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
	for ( auto it = menuObjects.begin(); it != menuObjects.end(); ++it )
	{
		ValidateLoop( menuObjects );
		( * it )->Draw( window );
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

void SceneGame::CreateTestLayer()
{
	sf::Texture& outsideTileset = game.GetTexture( "tiles/outside.png" );
	sf::Texture& fenceHorizontal = game.GetTexture( "scenery/fence_h.png" );
	sf::Texture& fenceVertical = game.GetTexture( "scenery/fence_v.png" );
	
	sf::Vector2i layerSize = Game::WindowSize / 32;
	layerSize.y *= 1.5;
	
	Tile grassTile( outsideTileset, 1, false );
	Tile dirtTile( outsideTileset, 0, false );
	Tile sandTile( outsideTileset, 2, false );
	Tile cropTile( outsideTileset, 3, false );
	Tile noCollideTile( outsideTileset, 255, true );
	
	layers.push_back( TileLayer( layerSize, grassTile ) );
	TileLayer& layer = layers[ 0 ];
	for ( size_t ix = 0; ix < layer.GetTiles().size(); ++ix )
	{
		for ( size_t iy = 0; iy < layer.GetTiles()[ ix ].size(); ++iy )
		{
			if ( ix == 0 or ix == layer.GetTiles().size() - 1 or iy == 0 or iy == layer.GetTiles()[ ix ].size() - 1 )
			{
				if ( ( ix >= 8 and ix <= 11 ) or ( iy >= 6 and iy <= 8 ) )
				{
					layer[ ix ][ iy ] = grassTile;
					continue;
				}
				
				layer[ ix ][ iy ] = noCollideTile;
				
				obj::Base* fence;
				if ( iy == 0 or iy == layer.GetTiles()[ ix ].size() - 1 )
				{
					fence = new obj::GridObject( ( * this ), fenceHorizontal, sf::Vector2i( ix, iy ) );
				}
				else
				{
					fence = new obj::GridObject( ( * this ), fenceVertical, sf::Vector2i( ix, iy ) );
				}
				gameObjects.push_back( boost::shared_ptr< obj::Base >( fence ) );
			}
			else if ( ix >= 8 and ix <= 10 and iy >= 8 and iy <= 10 )
			{
				layer[ ix ][ iy ] = cropTile;
			}
			else if ( ix >= 6 and ix <= 8 and iy >= 2 and iy <= 4 )
			{
				layer[ ix ][ iy ] = dirtTile;
			}
			else if ( ix >= 12 and ix <= 14 and iy >= 4 and iy <= 6 )
			{
				layer[ ix ][ iy ] = sandTile;
			}
		}
	}
}

void SceneGame::CreateTestObject()
{
	sf::Texture& texture = game.GetTexture( "characters/player.png" );
	player = boost::shared_ptr< obj::Player >( new obj::Player( ( * this ), texture, sf::Vector2i( 13, 5 ) ) );
	
	gameObjects.push_back( player );
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
	if ( typeid( * obj1 ) != typeid( obj::GridObject ) or typeid( * obj2 ) != typeid( obj::GridObject ) )
	{
		return false;
	}
	
	obj::GridObject* firstObj = static_cast< obj::GridObject* >( &( * obj1 ) );
	obj::GridObject* secondObj = static_cast< obj::GridObject* >( &( * obj2 ) );
	
	return ( -firstObj->GetGridPosition().y ) > ( -secondObj->GetGridPosition().y );
}
