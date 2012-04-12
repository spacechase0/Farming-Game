#include "game/World.h"

#include <fstream>
#include <iostream>

#include "game/NewFileData.h"
#include "game/objects/Npc.h"
#include "game/objects/Player.h"

void World::createNewSave( const NewFileData& data )
{
	setYear( 0 );
	setSeason( Spring );
	setDay( 0 );
	setTime( 60 * 6 );
	
	player.reset( new Player( ( * this ), data.name, data.gender, data.birthSeason, data.birthDay ) );
	player->setMap( 0 );
	player->setPosition( sf::Vector2f( 5.5f, 5.5f ) );
	
	initializeMaps();
	initializeNpcs();
}

bool World::loadSaveData( const std::string& filename )
{
	initializeMaps();
	initializeNpcs();
	
	return false;
}

bool World::saveSaveData( const std::string& filename ) const
{
	return false;
}

void World::update()
{
	if ( ++timeBuffer >= 50 )
	{
		timeBuffer -= 50;
		++time;
	}
	
	for ( auto it = npcs.begin(); it != npcs.end(); ++it )
	{
		it->get()->update();
	}
}

void World::setYear( sf::Uint16 theYear )
{
	year = theYear;
}

sf::Uint16 World::getYear() const
{
	return year;
}

void World::setSeason( Season season )
{
	if ( season >= 4 )
	{
		return;
	}
	
	sf::Uint8 s = season << 6;
	sf::Uint8 day = getDay();
	
	seasonAndDay = s | day;
}

Season World::getSeason() const
{
	return Season( ( 0xC0 & seasonAndDay ) >> 6 );
}

void World::setDay( sf::Uint8 day )
{
	if ( day >= 64 )
	{
		return;
	}
	
	sf::Uint8 season = getSeason() << 6;
	seasonAndDay = season | day;
}

sf::Uint8 World::getDay() const
{
	return 0x3F & seasonAndDay;
}

void World::setTime( sf::Uint16 theTime )
{
	if ( theTime >= 1440 )
	{
		return;
	}
	
	time = theTime;
}

sf::Uint16 World::getTime() const
{
	return time;
}

const std::vector< MapData >& World::getMaps() const
{
	return maps;
}

std::vector< MapData >& World::getMaps()
{
	return maps;
}

std::vector< std::shared_ptr< Npc > >& World::getNpcs()
{
	return npcs;
}

std::shared_ptr< const Player > World::getPlayer() const
{
	return std::const_pointer_cast< const Player >( player );
}

std::shared_ptr< Player > World::getPlayer()
{
	return player;
}

void World::initializeMaps()
{
	std::fstream file( "res/maps/maps.txt", std::fstream::in );
	if ( !file )
	{
		std::cout << "Failed to open 'res/maps/maps.txt'." << std::endl;
		return;
	}
	
	while ( true )
	{
		std::string line;
		std::getline( file, line );
		
		if ( !file )
		{
			break;
		}
		
		MapData map;
		if ( !map.loadFromFile( "res/maps/" + line ) )
		{
			std::cout << "Failed to load 'res/maps/" << line << "'." << std::endl;
			break;
		}
		
		maps.push_back( map );
	}
}

void World::initializeNpcs()
{
	npcs.push_back( std::static_pointer_cast< Npc >( player ) );
}
