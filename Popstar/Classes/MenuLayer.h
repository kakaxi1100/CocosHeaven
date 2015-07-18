#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

class MenuLayer :
	public Layer
{
public:
	CREATE_FUNC(MenuLayer);

	virtual bool init();

	void startGame();
};

