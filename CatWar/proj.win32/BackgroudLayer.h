#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class BackgroudLayer :
	public Node
{
public:
	CREATE_FUNC(BackgroudLayer);
	virtual bool init();

	void execute();
private:
	Sprite* img1;
	Sprite* img2;
};

