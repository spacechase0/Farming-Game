#ifndef OBJ_CAMERACONTROLLER_H
#define OBJ_CAMERACONTROLLER_H

#include "obj/Base.h"

namespace obj
{
	class CameraController : public obj::Base
	{
		public:
			CameraController( SceneGame& theGame, sf::RenderWindow& theWindow );
			
			virtual void Update();
			virtual void Update( const sf::Event& event );
			virtual void Draw( sf::RenderWindow& window );
		
		private:
			sf::RenderWindow& window;
			sf::View view;
	};
}

#endif // OBJ_CAMERACONTROLLER_H
