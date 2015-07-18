#pragma once
#include "cocos2d.h"
#include "MenuLayer.h"
USING_NS_CC;

class MenuScene :
	public Scene
{
public:
	CREATE_FUNC(MenuScene);
	virtual bool init();
private:
	MenuLayer* _ml;
};

