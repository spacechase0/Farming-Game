#ifndef PLAYER_H
#define PLAYER_H

#include "game/objects/Npc.h"

class Player : public Npc
{
	public:
		Player( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay );
		
		virtual void update();
		
		virtual std::string getName() const;
};

#endif // PLAYER_H
