#pragma once
#include "../cocos2d.h"
#include "BackgroudLayer.h"
#include "Cat.h"
#include "Dog.h"

USING_NS_CC;

class GameLayer :
	public Layer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();

	virtual void update(float delta);
private:

	//DrawNode* draw;
	void testMsg(Ref* pData);
	Cat* cat;
	Map<int, Dog*> dogs;

	BackgroudLayer* bgLayer;
};

