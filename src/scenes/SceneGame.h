#ifndef SCENES_SCENEGAME_H
#define SCENES_SCENEGAME_H

#include <vector>
#include <list>

#include "scenes/SceneBase.h"
#include "TileLayer.h"
#include "util/Grid.h"
#include "item/Items.h"

namespace obj
{
	class Base;
	class GridObject;
	class Player;
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
		
		bool IsTileEmpty( int x, int y, int layer = -1 );
		bool IsTileEmpty( sf::Vector2i pos, int layer = -1 );
		
		std::vector< TileLayer > layers;
		std::list< boost::shared_ptr< obj::Base > > objects;
		boost::shared_ptr< obj::Player > player;
		std::map< std::string, boost::shared_ptr< item::Item > > itemDefs;
	
	protected:
		void CreateTestLayer();
		void CreateTestObject();
		void DrawLayer( sf::RenderWindow& window, const TileLayer& layer ) const;
		
		void LoadItems( const std::string& filename );
		item::Item::Type ToType( const std::string& str );
		item::Tool::Action ToAction( const std::string& str );
		
		bool CompareObjects( const boost::shared_ptr< obj::Base >& obj1, const boost::shared_ptr< obj::Base >& obj2 );
};

#endif // SCENES_SCENEGAME_H
