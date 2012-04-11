#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <memory>
#include <SFML/Config.hpp>
#include <string>

#include "game/Season.h"
#include "game/MapData.h"

class NewFileData;
class Npc;
class Player;

class World
{
	public:
		void createNewSave( const NewFileData& data );
		bool loadSaveData( const std::string& filename );
		bool saveSaveData( const std::string& filename ) const;
		
		void update();
		
		void setYear( sf::Uint16 theYear );
		void setSeason( Season season );
		void setDay( sf::Uint8 day );
		void setTime( sf::Uint16 theTime );
		sf::Uint16 getYear() const;
		Season getSeason() const;
		sf::Uint8 getDay() const;
		sf::Uint16 getTime() const;
		
		std::vector< std::shared_ptr< Npc > >& getNpcs();
		std::shared_ptr< Player > getPlayer();
	
	private:
		sf::Uint16 year;
		sf::Uint8 seasonAndDay;
		sf::Uint16 time;
		
		std::vector< MapData > maps;
		std::vector< std::shared_ptr< Npc > > npcs;
		std::shared_ptr< Player > player;
		
		void initializeMaps();
		void initializeNpcs();
};

#endif // WORLD_H
