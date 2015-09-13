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

	bool onTouchBegan(Touch* touch , Event* event);
	void onTouchMove(Touch* touch, Event* event);
	void onTouchEnd(Touch* touch, Event* event);

	void hitDog(Dog* dog);
	void execute();

	Rect getHitRect();

	/*Rect temp1;
	Rect temp2;*/
private:
	Rect hitRect;
	int bulletDelay;

	Sprite* leftHand;
	Sprite* rightHand;

	void display();

	Map<int, FishboneBullet*> bullets;	
};

