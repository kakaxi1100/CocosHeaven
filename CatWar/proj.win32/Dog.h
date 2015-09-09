#pragma once
#include "../cocos2d.h"
#include "TubeBullet.h"
#include "GameData.h"

USING_NS_CC;

class Dog :
	public Node
{
public:
	CREATE_FUNC(Dog);

	virtual bool init();

	void execute();

	Rect getHitRect();
	void displayExplode();
private:
	int bulletDelay;
	Rect hitRect;

	void display();
	void distroy();

	Sprite* body;
	Sprite* explode;
	Sequence* actions;

	Map<int, TubeBullet*> bullets;
};

