#pragma once

#include "IBullet.h"

#include "../cocos2d.h"

USING_NS_CC;

class FishboneBullet :
	public Node, public IBullet
{
public:
	void excute() override;
};

