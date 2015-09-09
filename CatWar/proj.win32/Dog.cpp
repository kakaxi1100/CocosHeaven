#include "Dog.h"

bool Dog::init()
{
	if (!Node::init())
	{
		return false;
	}

	bulletDelay = 0;

	display();

	return true;
}

void Dog::display()
{
	//body
	body = Sprite::create("DrDog1.png");
	
	Animation* bodyAni = Animation::create();
	bodyAni->addSpriteFrameWithFile("DrDog1.png");
	bodyAni->addSpriteFrameWithFile("DrDog2.png");
	bodyAni->setLoops(-1);
	bodyAni->setDelayPerUnit(0.2f);

	Animate* bodyAct = Animate::create(bodyAni);
	addChild(body);
	body->runAction(bodyAct);

	//explode
	explode = Sprite::create("boom1.png");
	explode->setVisible(false);
	addChild(explode);

	hitRect = body->getBoundingBox();
}

void Dog::execute()
{
#if 0
	//产生子弹
	if (bulletDelay <= 0)
	{
		TubeBullet* tube = TubeBullet::create();
		tube->setID(GameData::getAvailableID());
		bullets.insert(tube->getID(), tube);
		tube->setPosition(this->getPosition());
		if (this->getParent() != nullptr)
		{
			this->getParent()->addChild(tube);
		}

		bulletDelay = 50;
	}
	bulletDelay--;

	//子弹运行
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		it->second->execute();
		//判断子弹是否已经超出范围
		if (it->second->getPositionY() < 0)
		{
			log("Dog :: { %d }", it->second->getID());
			TubeBullet* temp = bullets.at(it->first);
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
#endif
}

void Dog::distroy()
{
	this->removeChild(body, true);
	this->removeChild(explode, true);
	this->hitRect = Rect::ZERO;
	log("Dog %d Crashed!!", 1);
	NotificationCenter::getInstance()->postNotification("test", NULL);
}

void Dog::displayExplode()
{
	this->stopAllActions();
	Animation* explodeAnimation = Animation::create();
	char name[20];
	for (int i = 1; i <= 5; i++)
	{
		sprintf(name, "boom%d.png", i);
		explodeAnimation->addSpriteFrameWithFile(name);
	}
	explodeAnimation->setDelayPerUnit(0.2f);

	Animate* explodeAni = Animate::create(explodeAnimation);

	CallFunc* callFunc = CallFunc::create([&]()->void {distroy(); });

	actions = Sequence::create(explodeAni, callFunc, NULL);

	explode->setVisible(true);
	explode->runAction(actions);
}

Rect Dog::getHitRect()
{
	return hitRect;
}