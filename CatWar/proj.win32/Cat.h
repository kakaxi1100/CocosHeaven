#pragma once
#include "../cocos2d.h"
#include "IBullet.h"
#include "BulletManager.h"

USING_NS_CC;
using namespace std;
class Cat :
	public Sprite
{
public:
	CREATE_FUNC(Cat);
	virtual bool init();

	void setBullet(int pBulletType);

	bool onTouchBegan(Touch* touch , Event* event);
	void onTouchMove(Touch* touch, Event* event);
	void onTouchEnd(Touch* touch, Event* event);

	void excute();
private:
	int bulletType;
	int bulletDelay;

	Sprite* leftHand;
	Sprite* rightHand;

	void display();


};

