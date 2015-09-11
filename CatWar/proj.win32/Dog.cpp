#include "Dog.h"

bool Dog::init()
{
	if (!Node::init())
	{
		return false;
	}

	bulletDelay = 0;
	isReady = false;
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

	bodyAct = Animate::create(bodyAni);
	bodyAct->retain();
	addChild(body);


	//explode
	explode = Sprite::create("boom1.png");
	addChild(explode);

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
	actions->retain();

	hitRect = body->getBoundingBox();

	born();
}

void Dog::execute()
{
#if 0
	if (!isReady)
	{
		return;
	}
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
	body->setVisible(false);
	body->stopAllActions();
	explode->setVisible(false);
	explode->stopAllActions();
	isReady = false;
	log("Dog %d Crashed!!", id);
	born();
	NotificationCenter::getInstance()->postNotification("test", NULL);
}

void Dog::born()
{
	//reset
	body->setVisible(true);
	body->runAction(bodyAct);
	explode->setVisible(false);
	isReady = true;

	Size visualSize = Director::getInstance()->getVisibleSize();
	int type = random(0, 4);
}

void Dog::displayExplode()
{
	/*this->stopAllActions();*/

	explode->setVisible(true);
	explode->runAction(actions);
}

void Dog::onExit()
{
	Node::onExit();

	CC_SAFE_RELEASE(actions);
	CC_SAFE_RELEASE(bodyAct);
}

int Dog::getID()
{
	return id;
}

void Dog::setID(int value)
{
	id = value;
}

Rect Dog::getHitRect()
{
	return hitRect;
}