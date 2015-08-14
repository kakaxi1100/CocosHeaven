#pragma once
#include "../cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene :
	public Scene
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();

	static GameLayer* getGameLayer();
private:
	static GameLayer* gameLayer;
};

