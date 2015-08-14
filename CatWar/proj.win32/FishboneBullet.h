#pragma once

#include "IBullet.h"

#include "../cocos2d.h"

USING_NS_CC;

class FishboneBullet :
	public Node, public IBullet
{
public:
	CREATE_FUNC(FishboneBullet);

	virtual bool init();

	void excute() override;
	void bulletRelease() override;
	int getID() override;
	void setID(int value) override;
private:
	int id;
};

