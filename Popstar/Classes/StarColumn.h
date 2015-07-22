#pragma once

#include "cocos2d.h"
#include "Star.h"

USING_NS_CC;

//保存每条星星的状况
class StarColumn : public Node
{
public:
	CREATE_FUNC(StarColumn);
	bool init();
	void pushStar(Star* s);
	Star* getStarByIndex(int i);
	bool eraseStar(Star* s);
	bool eraseStarByIndex(int i);
	size_t getSize();
	void onExit();
	void setColNum(int value);
	int getColNum();
private:
	Vector<Star*> colStars;
	void changeStarsRow();
	void changeStarsCol();
	int mColNum;
};