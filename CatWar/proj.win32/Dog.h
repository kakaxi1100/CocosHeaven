#pragma once
#include "../cocos2d.h"
#include "TubeBullet.h"
#include "GameData.h"

USING_NS_CC;

class Cat;

class Dog :
	public Node
{
public:
	CREATE_FUNC(Dog);

	virtual bool init();

	void execute();

	Rect getHitRect();
	void displayExplode();

	virtual void onExit();

	int getID();
	void setID(int value);

	bool getReady();
	void hitCat(Cat * cat);
private:
	int id;
	bool isReady;
	int bulletDelay;
	Rect hitRect;

	void display();
	void distroy();
	void born();
	void move();

	Sprite* body;
	Animate* bodyAct;

	Sprite* explode;
	Sequence* actions;

	Map<int, TubeBullet*> bullets;
};

