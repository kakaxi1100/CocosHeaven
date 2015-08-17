#include "FishboneBullet.h"

bool FishboneBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* display = Sprite::create("YuGuZD.png");
	addChild(display);

	return true;
}

void FishboneBullet::bulletRelease()
{
	this->release();
}

void FishboneBullet::excute()
{
	//throw std::logic_error("The method or operation is not implemented.");

	this->setPositionY(this->getPositionY() + 5);
}

int FishboneBullet::getID()
{
	return id;
}

void FishboneBullet::setID(int value)
{
	id = value;
}