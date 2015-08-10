#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class Cat :
	public Node
{
public:
	CREATE_FUNC(Cat);

	virtual bool init();

	void display();
};

