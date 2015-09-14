#include "TubeBullet.h"

bool TubeBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* display = Sprite::create("DrDogZD.png");
	addChild(display);

	/*RotateBy* rotateBy = RotateBy::create(1, 360);
	RepeatForever* rp = RepeatForever::create(rotateBy);
	display->runAction(rp);*/
	hitRect = display->getBoundingBox();
	return true;
}

int TubeBullet::getID()
{
	return id;
}
void TubeBullet::setID(int value)
{
	id = value;
}

void TubeBullet::execute()
{
	this->setPositionY(this->getPositionY() - 8);
}

Rect TubeBullet::getHitRect()
{
	return hitRect;
}


