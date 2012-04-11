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
}

void GameScene::terminate()
{
}

void GameScene::update()
{
}

void GameScene::update( const sf::Event& event )
{
}

void GameScene::render( sf::RenderWindow& window )
{
}
