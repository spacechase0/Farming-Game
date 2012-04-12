#include "game/objects/Npc.h"

namespace
{
	void doWalkPart( const bool& shouldStop, bool& walking, Direction::Direction& facing, const Direction::Direction& nextDir )
	{
		if ( shouldStop )
		{
			walking = false;
		}
		else
		{
			facing = nextDir;
		}
	}
}

Npc::Npc( World& theWorld, const std::string& theName, Gender theGender, Season theBirthSeason, sf::Uint8 theBirthDay )
   : world( theWorld ),
     
     name( theName ),
     gender( theGender ),
	 birthSeason( theBirthSeason ),
	 birthDay( theBirthDay ),
	 
	 map( 0 ),
	 pos( 0, 0 ),
	 facing( Direction::Down ),
	 nextDir( Direction::Down ),
	 shouldStop( false ),
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
		sf::Vector2f prevPos = pos;
		switch ( facing )
		{
			case Direction::Up   : pos.y -= 0.09375; break;
			case Direction::Right: pos.x += 0.09375; break;
			case Direction::Down : pos.y += 0.09375; break;
			case Direction::Left : pos.x -= 0.09375; break;
		}
		
		if ( shouldStop or facing != nextDir )
		{
			if      ( facing == Direction::Up    and static_cast< int >( prevPos.y + 0.5 ) > static_cast< int >( pos.y + 0.5 ) )
			{
				pos.y = static_cast< int >( pos.y ) + 0.5;
				doWalkPart( shouldStop, walking, facing, nextDir );
			}
			else if ( facing == Direction::Right and static_cast< int >( prevPos.x + 0.5 ) < static_cast< int >( pos.x + 0.5 ) )
			{
				pos.x = static_cast< int >( pos.x ) + 0.5;
				doWalkPart( shouldStop, walking, facing, nextDir );
			}
			else if ( facing == Direction::Down  and static_cast< int >( prevPos.y + 0.5 ) < static_cast< int >( pos.y + 0.5 ) )
			{
				pos.y = static_cast< int >( pos.y ) + 0.5;
				doWalkPart( shouldStop, walking, facing, nextDir );
			}
			else if ( facing == Direction::Left  and static_cast< int >( prevPos.x + 0.5 ) > static_cast< int >( pos.x + 0.5 ) )
			{
				pos.x = static_cast< int >( pos.x ) + 0.5;
				doWalkPart( shouldStop, walking, facing, nextDir );
			}
		}
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

Direction::Direction Npc::getNextWalkingDirection() const
{
	return nextDir;
}

bool Npc::isWalking() const
{
	return walking;
}

void Npc::walk( Direction::Direction dir )
{std::cout<<"walk " << dir<<std::endl;
	nextDir = dir;
	if ( !walking )
	{
		facing = dir;
		walking = true;
	}
	shouldStop = false;
}

void Npc::stop()
{
	shouldStop = true;
}
