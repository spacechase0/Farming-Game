#include "game/objects/Npc.h"

Npc::Npc( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay )
   : world( theWorld ),
     
     name( theName ),
     gender( theGender ),
	 birthSeason( theBirthSeason ),
	 birthDay( theBirthDay ),
	 
	 map( 0 ),
	 pos( 0, 0 )
{
}

Npc::~Npc()
{
}

void Npc::update()
{
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
