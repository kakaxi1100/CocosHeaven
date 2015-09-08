#include "Cat.h"
#include "Dog.h"

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

	hitRect = body->getBoundingBox();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//注意绑定的用法，要传入this指针作为第一个参数
	//这个可以实现完美的事件机制！！！
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

void Cat::execute()
{
	//产生子弹
	if (bulletDelay <= 0)
	{
		FishboneBullet* fish = FishboneBullet::create();
		fish->setID(GameData::getAvailableID());
		bullets.insert(fish->getID(), fish);
		fish->setPosition(this->getPosition());
		if (this->getParent() != nullptr)
		{
			this->getParent()->addChild(fish);
		}

		bulletDelay = 50;
	}
	bulletDelay--;

	//子弹运行
	for (auto  it = bullets.begin(); it != bullets.end();)
	{
		it->second->execute();
		//判断子弹是否已经超出范围
		Size visualSize = Director::getInstance()->getVisibleSize();
		if (it->second->getPositionY() > visualSize.height)
		{
			log("Cat :: { %d }", it->second->getID());
			FishboneBullet* temp = bullets.at(it->first);
			auto parent = temp->getParent();
			if (parent != NULL)
			{
				parent->removeChild(temp, true);
			}
			//下一个迭代器定位的元素位置
			it = bullets.erase(it);
		}
		else
		{
			it++;
		}
	}


	//这里不能在循环内简单的这样使用erase ，具体原因请查看 C++ primer 关联容器一章
	/*for (auto &p : bullets)
	{
		p.second->execute();
		//判断子弹是否已经超出范围
		Size visualSize = Director::getInstance()->getVisibleSize();
		if (p.second->getPositionY() > visualSize.height)
		{
			log("{ %d }", p.second->getID());
			FishboneBullet* temp = bullets.at(p.first);
			auto parent = temp->getParent();
			if (parent != NULL)
			{
				parent->removeChild(temp);
			}
			bullets.erase(p.first);
			//temp->getParent()->removeChild(temp, true);
		}
	}*/
}

void Cat::hitDog(Dog* dog)
{
	//是否砸到狗
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		Rect temp1 = Rect(it->second->getPositionX(), it->second->getPositionY(), it->second->getHitRect().size.width, it->second->getHitRect().size.height);
		Rect temp2 = Rect(dog->getPositionX(), dog->getPositionY(), dog->getHitRect().size.width, dog->getHitRect().size.height);

		if (temp1.intersectsRect(temp2))
		{
			log("Cat Hit:: { %d }", it->second->getID());
			FishboneBullet* temp = bullets.at(it->first);
			auto parent = temp->getParent();
			if (parent != NULL)
			{
				parent->removeChild(temp, true);
			}
			//狗狗爆炸
			
			//下一个迭代器定位的元素位置
			it = bullets.erase(it);
		}
		else
		{
			it++;
		}
	}
}

Rect Cat::getHitRect()
{
	return hitRect;
}

