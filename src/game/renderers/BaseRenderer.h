#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <memory>

namespace sf
{
	class RenderWindow;
}
class GameObject;
class World;

class BaseRenderer
{
	public:
		BaseRenderer( std::shared_ptr< GameObject > theObject );
		virtual ~BaseRenderer();
		
		virtual void render( sf::RenderWindow& window, const World& world ) = 0;
	
	protected:
		std::shared_ptr< GameObject > object;
};

#endif // BASERENDERER_H
