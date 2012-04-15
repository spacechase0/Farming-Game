#ifndef PLAYER_H
#define PLAYER_H

#include "game/objects/Npc.h"

class Player : public Npc
{
	public:
		Player( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay );
		
		sf::Uint16 getFatigue() const;
		sf::Uint16 getFatigueMax() const;
		sf::Uint16 getStarvation() const;
		sf::Uint16 getStarvationMax() const;
		
		virtual std::string getType() const;
	
	private:
		sf::Uint16 fatigue;
		sf::Uint16 starvation;
};

#endif // PLAYER_H
