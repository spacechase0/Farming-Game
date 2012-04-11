#include "game/World.h"

#include <fstream>
#include <iostream>

#include "game/NewFileData.h"

void World::createNewSave( const NewFileData& data )
{
	setYear( 0 );
	setSeason( Spring );
	setDay( 0 );
	setTime( 60 * 6 );
	
	initializeMaps();
}

bool World::loadSaveData( const std::string& filename )
{
	initializeMaps();
	
	return false;
}

bool World::saveSaveData( const std::string& filename ) const
{
	return false;
}

void World::update()
{
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
