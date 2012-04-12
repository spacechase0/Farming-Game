#ifndef NPC_H
#define NPC_H

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "game/Direction.h"
#include "game/Gender.h"
#include "game/objects/GameObject.h"
#include "game/Season.h"

class World;

class Npc : public GameObject
{
	public:
		Npc( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay );
		virtual ~Npc();
		
		virtual void update();
		
		std::string getName() const;
		Gender getGender() const;
		Season getBirthSeason() const;
		sf::Uint8 getBirthDay() const;
		
		void setMap( sf::Uint16 theMap );
		sf::Uint16 getMap() const;
		
		void setPosition( sf::Vector2f thePos );
		sf::Vector2f getPosition() const;
		
		Direction::Direction getFacingDirection() const;
		Direction::Direction getNextWalkingDirection() const;
		bool isWalking() const;
		void walk( Direction::Direction dir );
		void stop();
	
	protected:
		World& world;
		
		const std::string name;
		const Gender gender;
		const Season birthSeason;
		const sf::Uint8 birthDay;
		
		sf::Uint16 map;
		sf::Vector2f pos;
		Direction::Direction facing;
		Direction::Direction nextDir;
		bool shouldStop;
		bool walking;
};

#endif // NPC_H
