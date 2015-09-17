#include "BackgroudLayer.h"

bool BackgroudLayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	img1 = Sprite::create("bg.png");
	img1->setAnchorPoint(Vec2::ZERO);
	img1->setPosition(Vec2::ZERO);
	addChild(img1);

	img2 = Sprite::create("bg.png");
	img2->setAnchorPoint(Vec2::ZERO);
	img2->setPosition(0.0f, img1->getContentSize().height);
	addChild(img2);

	return true;
}

void BackgroudLayer::execute()
{
	img1->setPositionY(img1->getPositionY() - 2);
	img2->setPositionY(img2->getPositionY() - 2);
	if (img1->getPositionY() + img1->getContentSize().height < 0)
	{
		img1->setPositionY(img2->getPositionY() + img2->getContentSize().height);
	}

	if (img2->getPositionY() + img2->getContentSize().height < 0)
	{
		img2->setPositionY(img1->getPositionY() + img1->getContentSize().height);
	}
}
