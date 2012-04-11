#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <map>
#include <string>

namespace sf
{
	class Event;
	class RenderWindow;
}
class World;

class GameInterface
{
	public:
		void initialize( World& world );
		void terminate();
		
		void update( const sf::Event& event, const World& world );
		void render( sf::RenderWindow& window, const World& world );
	
	private:
		void renderWorld( sf::RenderWindow& window, const World& world );
		void renderInterface( sf::RenderWindow& window, const World& world );
};

#endif // GAMEINTERFACE_H
