#include "MenuScene.h"

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_ml = MenuLayer::create();
	this->addChild(_ml);

	return true;
}

