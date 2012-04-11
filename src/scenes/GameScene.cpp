#include "scenes/GameScene.h"

#include "game/NewFileData.h"

GameScene::GameScene( Game& theGame )
   : Scene::Scene( theGame )
{
}

void GameScene::initialize( SceneChangeEvent& event )
{
	NewFileData data;
	world.createNewSave( data );
	interface.initialize( world );
}

void GameScene::terminate()
{
	interface.terminate();
}

void GameScene::update()
{
	world.update();
}

void GameScene::update( const sf::Event& event )
{
	interface.update( event, world );
}

void GameScene::render( sf::RenderWindow& window )
{
	interface.render( window, world );
}
