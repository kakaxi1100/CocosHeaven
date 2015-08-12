#pragma once
#include "../cocos2d.h"
#include "Cat.h"
#include "Dog.h"
#include "BulletManager.h"

USING_NS_CC;

class GameLayer :
	public Layer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();

	virtual void update(float delta);
private:
	Cat* cat;
};

