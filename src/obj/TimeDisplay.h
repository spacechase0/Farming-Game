#ifndef OBJ_TIMEDISPLAY_H
#define OBJ_TIMEDISPLAY_H

#include "obj/Base.h"

namespace obj
{
	class TimeDisplay : public obj::Base
	{
		public:
			TimeDisplay( SceneGame& theGame );
			
			virtual void Draw( sf::RenderWindow& window );
			
			virtual int GetDepth() const;
			
		private:
			sf::Image timeGradient;
	};
}

#endif // OBJ_TIMEDISPLAY_H

