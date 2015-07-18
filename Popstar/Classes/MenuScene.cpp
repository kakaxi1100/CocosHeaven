#include "MenuScene.h"

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	Size visiableSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visiableSize.width / 2, visiableSize.height/2);
	this->addChild(background);

	_ml = MenuLayer::create();
	this->addChild(_ml);

	return true;
}

