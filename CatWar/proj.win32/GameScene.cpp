#include "GameScene.h"


bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	GameLayer* gamelayer = GameLayer::create();
	addChild(gamelayer);

	return true;
}
