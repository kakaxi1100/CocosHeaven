#include "MenuLayer.h"

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visualSize = Director::getInstance()->getVisibleSize();

	Sprite* menuBG = Sprite::create("bg.png");
	addChild(menuBG);

	Sprite* title1 = Sprite::create("meowstar.png");
	title1->setPosition(0, (this->getContentSize().height - title1->getContentSize().height)/2);
	addChild(title1);

	Sprite* title2 = Sprite::create("battle.png");
	title2->setPosition(title1->getPositionX(), title1->getPositionY() - title1->getContentSize().height/2);
	addChild(title2);

	return true;
}
