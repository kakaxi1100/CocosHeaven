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

	Dog* dog = Dog::create();
	dog->setPosition(300, 600);
	addChild(dog);

	return true;
}

void GameLayer::update(float delta)
{
	
}
