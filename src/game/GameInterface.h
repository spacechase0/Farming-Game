#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <functional>
#include <map>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <util/unsorted_map.h>

namespace sf
{
	class Event;
	class RenderWindow;
}
class BaseRenderer;
class GameObject;
class World;

class GameInterface
{
	public:
		void initialize( World& world );
		void terminate();
		
		void update( const sf::Event& event, World& world );
		void render( sf::RenderWindow& window, World& world );
	
	private:
		std::map< std::string, std::function< std::shared_ptr< BaseRenderer >( std::shared_ptr< GameObject > ) > > rendererMapping;
		util::unsorted_map< GameObject*, std::shared_ptr< BaseRenderer > > renderers;
		sf::Clock rendererClearTimer;
		
		sf::View worldView;
		void renderWorld( sf::RenderWindow& window, World& world );
		void renderInterface( sf::RenderWindow& window, World& world );
		
		struct
		{
			sf::Sprite sky;
			sf::Sprite stars;
			
			sf::Sprite glow;
			sf::Sprite moon;
			sf::Sprite sun;
			
			sf::Sprite ground;
			sf::Sprite rim;
		} time;
		
		struct
		{
			sf::Sprite back;
			sf::Sprite fat;
			sf::Sprite star;
		} bars;
};

#endif // GAMEINTERFACE_H
