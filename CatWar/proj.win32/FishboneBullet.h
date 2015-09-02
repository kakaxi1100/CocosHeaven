#pragma once

#include "../cocos2d.h"

USING_NS_CC;

class FishboneBullet :
	public Node
{
public:
	CREATE_FUNC(FishboneBullet);

	virtual bool init();
	int getID();
	void setID(int value);
	void execute();
	Rect getHitRect();
private:
	int id;
	Rect hitRect;
};

