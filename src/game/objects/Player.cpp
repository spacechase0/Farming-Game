#include "game/objects/Player.h"

Player::Player( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay )
   : Npc::Npc( theWorld, theName, theGender, theBirthSeason, theBirthDay ),
     fatigue( 100 ),
     starvation( 100 )
{
}

sf::Uint16 Player::getFatigue() const
{
	return fatigue;
}

sf::Uint16 Player::getFatigueMax() const
{
	return 100;
}

sf::Uint16 Player::getStarvation() const
{
	return starvation;
}

sf::Uint16 Player::getStarvationMax() const
{
	return 100;
}

std::string Player::getType() const
{
	return "Player";
}
