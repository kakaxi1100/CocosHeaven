#include "Cat.h"

bool Cat::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	bulletDelay = 0;

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

	//left hand
	leftHand = Sprite::create("catHand1.png");
	leftHand->setAnchorPoint(Point(1, 0.5));
	leftHand->setPosition(-18, -20);
	addChild(leftHand);

	//right hand
	rightHand = Sprite::create("catHand2.png");
	rightHand->setAnchorPoint(Point(0, 0.5));
	rightHand->setPosition(18, -20);
	addChild(rightHand);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Cat::onTouchBegan, this);//std::bind(&Cat::onTouchBegan,this, _1, _2);
	listener->onTouchMoved = CC_CALLBACK_2(Cat::onTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(Cat::onTouchEnd, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, body);
}

bool Cat::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();//取得点击时的坐标点，GL坐标
	pos = this->convertToNodeSpace(pos);//转化为节点坐标系
	auto target = (Sprite*)event->getCurrentTarget();
	log("{ %f , %f }", pos.x, pos.y);
	Rect rect = target->getBoundingBox();
	log("{ %f, %f, %f, %f }", rect.getMinX(), rect.getMaxY(), rect.size.width, rect.size.height);
	if (target->getBoundingBox().containsPoint(pos))
	{
		log("Touch it!!!");

		this->setPosition(this->getParent()->convertToNodeSpace(touch->getLocation()));
	}
	else
	{
		return false;
	}
	return true;
}

void Cat::onTouchMove(Touch* touch, Event* event)
{
	this->setPosition(this->getParent()->convertToNodeSpace(touch->getLocation()));
		
}

void Cat::onTouchEnd(Touch* touch, Event* event)
{
	
}

void Cat::setBullet(int pBulletType)
{
	bulletType = pBulletType;
}

void Cat::excute()
{
	if (bulletDelay <= 0)
	{
		BulletManager::addBullet(bulletType);
		bulletDelay = 60;
	}
	bulletDelay--;
}

