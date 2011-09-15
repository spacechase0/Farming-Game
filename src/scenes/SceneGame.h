#ifndef SCENES_SCENEGAME_H
#define SCENES_SCENEGAME_H

#include <vector>
#include <list>

#include "scenes/SceneBase.h"
#include "TileLayer.h"
#include "util/Grid.h"

namespace obj
{
	class Base;
	class GridObject;
}

class SceneGame : public SceneBase
{
	public:
		SceneGame( Game& game );
		
		virtual void Initialize();
		virtual void Terminate();
		
		virtual void Update( sf::RenderWindow& window );
		virtual void Update( sf::RenderWindow& window, const sf::Event& event );
		virtual void Draw( sf::RenderWindow& window );
		
		std::vector< TileLayer > layers;
		std::list< boost::shared_ptr< obj::Base > > objects;
	
	protected:
		void CreateTestLayer();
		void CreateTestObject();
		void DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const;
		
		bool CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 );
};

#endif // SCENES_SCENEGAME_H
