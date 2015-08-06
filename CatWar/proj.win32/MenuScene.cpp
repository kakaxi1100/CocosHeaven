#include "MenuScene.h"

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visiableSize = Director::getInstance()->getVisibleSize();

	MenuLayer* menuLayer = MenuLayer::create();
	menuLayer->setPosition(visiableSize.width / 2, visiableSize.height / 2);
	addChild(menuLayer);
	
	return true;
}