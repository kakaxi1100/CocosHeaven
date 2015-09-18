#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class GameOverLayer :
	public Layer
{
public:
	CREATE_FUNC(GameOverLayer);

	virtual bool init();
	void backToMenu();
};

