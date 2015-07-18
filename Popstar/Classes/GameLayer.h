#pragma once

#include "cocos2d.h"
#include "FloatWord.h"
#include "StarMatrix.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);

	void showStarMatrix();

private:
};
