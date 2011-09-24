#include "obj/Npc.h"

#include "Game.h"
#include "scenes/SceneGame.h"
#include "util/Type.h"

namespace obj
{
	Npc::Npc( SceneGame& theGame, MapManager::Map& theMap, sf::Texture& theTexture, sf::Vector2i theFrameSize )
	   : RenderObject::RenderObject( theGame, theTexture, sf::Vector2f( 0, 0 ) ),
	     map( &theMap ),
	     frameSize( theFrameSize )
	{
		sf::IntRect subRect( frameSize.x * Down, frameSize.y * 0, frameSize.x, frameSize.y );
		sprite.SetSubRect( subRect );
	}
	
	void Npc::Update()
	{
		RenderObject::Update();
	}
	
	void Npc::Update( const sf::Event& event )
	{
		RenderObject::Update( event );
	}
	
	void Npc::Draw( sf::RenderWindow& window )
	{
		RenderObject::Draw( window );
	}
	
	void Npc::SetMap( MapManager::Map& theMap )
	{
		boost::shared_ptr< obj::Base > alive;
		
		auto it = map->objects.begin();
		for ( ; it != map->objects.end(); ++it )
		{
			if ( it->get() != this )
			{
				continue;
			}
			
			alive = ( * it );
			break;
		}
		
		game.maps.AddGarbage( it, &map->objects );
		theMap.objects.push_back( alive );
	}
	
	MapManager::Map& Npc::GetMap() const
	{
		return ( * map );
	}
	
	sf::Vector2i Npc::GetGridPosition() const
	{
		sf::Vector2i gridPos( sprite.GetPosition().x, sprite.GetPosition().y );
		gridPos -= sf::Vector2i( Game::TileSize / 2, Game::TileSize / 2 );
		gridPos.x /= Game::TileSize;
		gridPos.y /= Game::TileSize;
		return gridPos;
	}
	
	void Npc::MoveInDirection( MovementDirection dir, float speed )
	{
		sf::Vector2f pos = sprite.GetPosition();
		switch ( dir )
		{
			case Up:
				pos.y -= speed;
				break;
			
			case Down:
				pos.y += speed;
				break;
			
			case Left:
				pos.x -= speed;
				break;
			
			case Right:
				pos.x += speed;
				break;
			
			// Gets rid of "warning: enumeration value 'None' not handled in switch"
			default:
				break;
		}
		
		sf::FloatRect rect( pos.x, pos.y, Game::TileSize, Game::TileSize );
		for ( auto it = map->objects.begin(); it != map->objects.end(); ++it )
		{
			if ( !util::IsOfType< obj::RenderObject* >( it->get() ) )
			{
				continue;
			}
			
			obj::RenderObject* object = static_cast< obj::RenderObject* >( it->get() );
			if ( !object->CanCollide() )
			{
				continue;
			}
			
			if ( object->GetCollisionRect().Intersects( rect ) )
			{
				object->CollidedWith( this );
				this->CollidedWith( object );
				
				if ( object->IsSolid() )
				{
					return; 
				}
			}
		}
		
		sprite.SetPosition( pos );
	}
}
