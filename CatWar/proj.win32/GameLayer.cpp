#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	cat = Cat::create();
	cat->setPosition(200, 400);
	addChild(cat);

	dog = Dog::create();
	dog->setPosition(300, 600);
	addChild(dog);

	this->scheduleUpdate();

	return true;
}

void GameLayer::update(float delta)
{
	cat->execute();
	cat->hitDog(dog);

	dog->execute();
}
