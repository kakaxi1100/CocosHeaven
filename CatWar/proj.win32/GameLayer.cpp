#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Cat* cat = Cat::create();
	cat->setPosition(200, 400);
	addChild(cat);

	return true;
}
