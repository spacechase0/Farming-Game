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
	class CameraController;
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
		
		enum GarbageType
		{
			GameGarbage,
			MenuGarbage
		};
		typedef boost::shared_ptr< obj::Base > ObjectPtr;
		typedef std::list< ObjectPtr > ObjectList;
		typedef std::pair< ObjectList::iterator, GarbageType > Garbage;
		typedef boost::shared_ptr< item::Item > ItemPtr;
		
		std::vector< TileLayer > layers;
		ObjectList gameObjects;
		ObjectList menuObjects;
		std::list< Garbage > garbageObjects;
		std::map< std::string, ItemPtr > itemDefs;
		
		obj::Player* player;
		obj::CameraController* cameraController;
		bool simulateWorld;
		
		void CreateChatDialog( const std::vector< std::string >& messages );
	
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
