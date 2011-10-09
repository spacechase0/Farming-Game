#ifndef OBJ_WEATHERDISPLAY_H
#define OBJ_WEATHERDISPLAY_H

#include "obj/Base.h"

namespace obj
{
	class WeatherDisplay : public obj::Base
	{
		public:
			WeatherDisplay( SceneGame& theGame, sf::Texture& theRainTexture );
			
			virtual void Draw( sf::RenderWindow& window );
			
			virtual int GetDepth() const;
		
		private:
			float weatherHeight;
			sf::Texture& rainTexture;
	};
}

#endif // OBJ_WEATHERDISPLAY_H


