#include "FishboneBullet.h"

bool FishboneBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* display = Sprite::create("YuGuZD.png");
	addChild(display);

	hitRect = display->getBoundingBox();

	/*DrawNode* draw = DrawNode::create();
	this->addChild(draw);
	Vec2 point1[4];
	point1[0] = Point(hitRect.getMinX(), hitRect.getMaxY());
	point1[1] = Point(hitRect.getMaxX(), hitRect.getMaxY());
	point1[2] = Point(hitRect.getMaxX(), hitRect.getMinY());
	point1[3] = Point(hitRect.getMinX(), hitRect.getMinY());
	draw->drawPolygon(point1, 4, Color4F(1, 0, 0, 0), 1, Color4F(1, 0, 0, 1));*/
	

	return true;
}

void FishboneBullet::execute()
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

Rect FishboneBullet::getHitRect()
{
	return hitRect;
}