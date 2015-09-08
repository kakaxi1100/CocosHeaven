#pragma once

#include "../cocos2d.h"

USING_NS_CC;

class TubeBullet :
	public Node
{
public:
	CREATE_FUNC(TubeBullet);

	virtual bool init();
	int getID();
	void setID(int value);
	void execute();
	Rect getHitRect();
private:
	Rect hitRect;
	int id;
};

