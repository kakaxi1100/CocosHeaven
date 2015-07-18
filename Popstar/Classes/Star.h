#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Star
	: public Sprite
{
public:
	bool init(int pType);	
	static Star* create(int pType);

	int type;

	int col;
	int row;

	void setIsActive(bool value);
	bool getIsAvctive();

	void update(float dt);
private:
	bool mIsActive;
	//SpriteFrame* normal;
	//SpriteFrame* select;

	std::string normalPNG;
	std::string selectPNG;
};