#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//Audio::getInstance()->playBGM();

	GameLayer* ss = GameLayer::create();
	this->addChild(ss);

	return true;
}