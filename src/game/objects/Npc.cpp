#include "game/objects/Npc.h"

Npc::Npc( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay )
   : world( theWorld ),
     
     name( theName ),
     gender( theGender ),
	 birthSeason( theBirthSeason ),
	 birthDay( theBirthDay ),
	 
	 map( 0 ),
	 pos( 0, 0 ),
	 facing( Direction::Down ),
	 walking( false )
{
}

Npc::~Npc()
{
}

void Npc::update()
{
	// TO DO: Check collisions
	if ( walking )
	{
		switch ( facing )
		{
			case Direction::Up   : pos.y -= 0.09375; break;
			case Direction::Right: pos.x += 0.09375; break;
			case Direction::Down : pos.y += 0.09375; break;
			case Direction::Left : pos.x -= 0.09375; break;
		};
	}
}

std::string Npc::getName() const
{
	return name;
}

Gender Npc::getGender() const
{
	return gender;
}

Season Npc::getBirthSeason() const
{
	return birthSeason;
}

sf::Uint8 Npc::getBirthDay() const
{
	return birthDay;
}

void Npc::setMap( sf::Uint16 theMap )
{
	map = theMap;
}

sf::Uint16 Npc::getMap() const
{
	return map;
}

void Npc::setPosition( sf::Vector2f thePos )
{
	pos = thePos;
}

sf::Vector2f Npc::getPosition() const
{
	return pos;
}

Direction::Direction Npc::getFacingDirection() const
{
	return facing;
}

bool Npc::isWalking() const
{
	return walking;
}

void Npc::walk( Direction::Direction dir )
{
	facing = dir;
	walking = true;
}

void Npc::stop()
{
	walking = false;
}
