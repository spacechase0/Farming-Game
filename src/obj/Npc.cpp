#include "obj/Npc.h"

namespace obj
{
	const float Npc::RenderOffsetThreshold = Game::TileSize;
	
	Npc::Npc( SceneGame& theGame, sf::Texture& theTexture, sf::Vector2i theFrameSize )
	   : GridObject::GridObject( theGame, theTexture, sf::Vector2i( 0, 0 ) ),
	     movement( None ), nextDir( None ),
	     renderOffset( 0 ),
	     renderOffsetSpeed( 3.25 ),
	     frameSize( theFrameSize )
	     
	{
		sf::IntRect subRect( frameSize.x * Down, frameSize.y * 0, frameSize.x, frameSize.y );
		sprite.SetSubRect( subRect );
	}
	
	void Npc::Update()
	{
		GridObject::Update();
		if ( movement != None )
		{
			if ( IsDirectionEmpty( movement ) )
			{
				renderOffset += ( Game::SimulationRate / Game::TileSize ) * renderOffsetSpeed;
			}
			else
			{
				renderOffset = 0;
				movement = nextDir;
			}
			
			if ( renderOffset >= RenderOffsetThreshold )
			{
				renderOffset -= RenderOffsetThreshold;
				switch ( movement )
				{
					case Up:    --gridPos.y; break;
					case Down:  ++gridPos.y; break;
					case Left:  --gridPos.x; break;
					case Right: ++gridPos.x; break;
					default:    break; // Gets rid of "warning: enumeration value 'None' not handled in switch"
				}
				SetGridPosition( gridPos ); // Take a look at GridObject::SetGridPosition to see why. :P
				movement = nextDir;
			}
		}
		else
		{
			renderOffset = 0;
			movement = nextDir;
		}
	}
	
	void Npc::Update( const sf::Event& event )
	{
		GridObject::Update( event );
	}
	
	void Npc::Draw( sf::RenderWindow& window )
	{
		float moveX = 0.f, moveY = 0.f;
		switch ( movement )
		{
			case Up:    moveY = -renderOffset; break;
			case Down:  moveY = renderOffset;  break;
			case Left:  moveX = -renderOffset; break;
			case Right: moveX = renderOffset;  break;
			default: break;
		}
		
		if ( movement != None )
		{
			int direction = static_cast< int >( movement );
			sf::IntRect subRect( frameSize.x * direction, frameSize.y * 0, frameSize.x, frameSize.y );
			sprite.SetSubRect( subRect );
		}
		
		sprite.Move( moveX, moveY );
		GridObject::Draw( window );
		sprite.Move( -moveX, -moveY );
	}
	
	void Npc::Walk( MovementDirection theNextDir )
	{
		nextDir = theNextDir;
	}
	
	void Npc::StopWalking()
	{
		nextDir = None;
	}
	
	bool Npc::IsDirectionEmpty( MovementDirection& dir )
	{
		sf::Vector2i nextGridPos = gridPos;
		switch ( movement )
		{
			case Up:    --nextGridPos.y; break;
			case Down:  ++nextGridPos.y; break;
			case Left:  --nextGridPos.x; break;
			case Right: ++nextGridPos.x; break;
			default:    break; // Gets rid of "warning: enumeration value 'None' not handled in switch"
		}
		
		return !game.IsTileEmpty( nextGridPos );
	}
}
