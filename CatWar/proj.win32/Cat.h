#pragma once
#include "../cocos2d.h"
#include "IBullet.h"

USING_NS_CC;

class Cat :
	public Sprite
{
public:
	CREATE_FUNC(Cat);
	virtual bool init();

	void setBullet(IBullet* pBullet);

	bool onTouchBegan(Touch* touch , Event* event);
	void onTouchMove(Touch* touch, Event* event);
	void onTouchEnd(Touch* touch, Event* event);
private:
	IBullet* bullet;

	Sprite* leftHand;
	Sprite* rightHand;

	void display();


	void excute();
};

