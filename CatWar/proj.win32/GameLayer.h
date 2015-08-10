#pragma once
#include "../cocos2d.h"
#include "Cat.h"

USING_NS_CC;

class GameLayer :
	public Layer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();
};

