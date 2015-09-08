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
	Animation* explodeAnimation = Animation::create();
	explodeAnimation->addSpriteFrameWithFile("boom1.png");
	explodeAnimation->addSpriteFrameWithFile("boom2.png");
	explodeAnimation->addSpriteFrameWithFile("boom3.png");
	explodeAnimation->addSpriteFrameWithFile("boom4.png");
	explodeAnimation->addSpriteFrameWithFile("boom5.png");
	explodeAnimation->setDelayPerUnit(0.2f);

	explodeAni = Animate::create(explodeAnimation);

	hitRect = body->getBoundingBox();
}

void Dog::execute()
{
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
}

void Dog::distroy()
{
	this->removeChild(body, true);
}

void Dog::displayExplode()
{

}

Rect Dog::getHitRect()
{
	return hitRect;
}