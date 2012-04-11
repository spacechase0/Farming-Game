#ifndef NEWFILEDATA_H
#define NEWFILEDATA_H

#include <string>

#include "game/Gender.h"
#include "game/Season.h"

class NewFileData
{
	public:
		NewFileData();
		
		std::string name;
		Gender gender;
		Season birthSeason;
		sf::Uint8 birthDay;
};

#endif // NEWFILEDATA_H
