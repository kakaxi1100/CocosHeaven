#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class Cat :
	public Sprite
{
public:
	CREATE_FUNC(Cat);

	virtual bool init();

	Sprite* leftHand;
	Sprite* rightHand;

	void display();
	void initEvent();

	bool onTouchBegan(Touch* touch , Event* event);
	void onTouchMove(Touch* touch, Event* event);
	void onTouchEnd(Touch* touch, Event* event);
};

