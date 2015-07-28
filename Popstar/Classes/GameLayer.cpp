#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visiableSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visiableSize.width / 2, visiableSize.height / 2);
	this->addChild(background);

	StarMatrix* s = StarMatrix::create();
	addChild(s);

	return true;
}