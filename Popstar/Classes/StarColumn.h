#pragma once

#include "cocos2d.h"
#include "Star.h"

USING_NS_CC;

//����ÿ�����ǵ�״��
class StarColumn : public Node
{
public:
	CREATE_FUNC(StarColumn);
	bool init();
	void pushStar(Star* s);
	Star* getStarByIndex(int i);
	size_t getSize();
	void onExit();
private:
	Vector<Star*> colStars;
};