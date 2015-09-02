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
private:
	int bulletDelay;
	Rect hitRect;

	void display();
	void distroy();
	void displayExplode();

	Sprite* body;
	Sprite* explode;

	Map<int, TubeBullet*> bullets;
};

