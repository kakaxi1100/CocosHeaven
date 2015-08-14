#include "GameScene.h"

GameLayer* GameScene::gameLayer = NULL;

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	gameLayer = GameLayer::create();
	addChild(gameLayer);

	return true;
}

GameLayer* GameScene::getGameLayer()
{
	return gameLayer;
}
