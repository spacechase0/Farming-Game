#include "game/objects/Player.h"

Player::Player( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay )
   : Npc::Npc( theWorld, theName, theGender, theBirthSeason, theBirthDay )
{
}

void Player::update()
{
}

std::string Player::getType() const
{
	return "Player";
}
