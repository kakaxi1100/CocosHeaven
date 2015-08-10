#include "Cat.h"

bool Cat::init()
{
	if (!Node::init())
	{
		return false;
	}

	display();
	initEvent();

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
}

void Cat::initEvent()
{
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = std::bind(&Cat::onTouchBegan, _1, _2);//CC_CALLBACK_2(Cat::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Cat::onTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(Cat::onTouchEnd, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Cat::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();//取得点击时的坐标点，GL坐标

	return true;
}

void Cat::onTouchMove(Touch* touch, Event* event)
{

	this->setPosition(touch->getLocation());
	log("hhhhhhhhhh");
}

void Cat::onTouchEnd(Touch* touch, Event* event)
{
	
}
