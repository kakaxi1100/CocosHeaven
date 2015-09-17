#pragma once
#include "../cocos2d.h"
#include "FishboneBullet.h"
#include "GameData.h"

class Dog;

USING_NS_CC;
using namespace std;
class Cat :
	public Node
{
public:
	CREATE_FUNC(Cat);
	virtual bool init();
	virtual void onExit();

	bool onTouchBegan(Touch* touch , Event* event);
	void onTouchMove(Touch* touch, Event* event);
	void onTouchEnd(Touch* touch, Event* event);

	void hitDog(Dog* dog);
	void execute();

	Rect getHitRect();
	void displayExplode();
	bool getReady();
	void setReady(bool value);
	/*Rect temp1;
	Rect temp2;*/
private:
	bool isReady;
	Rect hitRect;
	int bulletDelay;

	Sprite* leftHand;
	Sprite* rightHand;

	void display();
	void born();
	void distroy();

	Sprite* body;
	Animate* bodyAct;

	Sprite* tail;
	RepeatForever* tailAct;

	Sprite* explode;
	Sequence* actions;

	Map<int, FishboneBullet*> bullets;	
};

