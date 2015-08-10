#include "Cat.h"

bool Cat::init()
{
	if (!Node::init())
	{
		return false;
	}

	display();

	return true;
}

void Cat::display()
{

	//body
	Sprite* body = Sprite::create("catBody1.png");
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFile("catBody1.png");
	animation->addSpriteFrameWithFile("catBody2-4.png");
	animation->addSpriteFrameWithFile("catBody3.png");
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	Animate* bodyAct = Animate::create(animation);
	addChild(body);
	body->runAction(bodyAct);

	//tail
	Sprite* tail = Sprite::create("catTail.png");
	tail->setAnchorPoint(Point(0.5, 1));
	tail->setScale(0.3f);
	tail->setPosition(0,-30);
	/*RotateBy* rotateBy = RotateBy::create(0.5f, 30);
	RepeatForever* rotateForever = RepeatForever::create(rotateBy);*/
	RepeatForever* tailAct = RepeatForever::create(Sequence::create(RotateBy::create(0.5f, 40), RotateBy::create(0.5f, -40), nullptr));

	addChild(tail);
	tail->runAction(tailAct);
}
