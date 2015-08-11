#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class Dog :
	public Node
{
public:
	CREATE_FUNC(Dog);

	virtual bool init();

	void display();
};

