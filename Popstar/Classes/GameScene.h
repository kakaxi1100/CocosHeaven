#pragma once

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	virtual bool init();

	CREATE_FUNC(GameScene);
};
