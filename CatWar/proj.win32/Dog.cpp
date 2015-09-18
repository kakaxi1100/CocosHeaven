#include "Dog.h"
#include "Cat.h"

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

	/*DrawNode* draw = DrawNode::create();
	this->addChild(draw);
	Vec2 point1[4];
	point1[0] = Point(hitRect.getMinX(), hitRect.getMaxY());
	point1[1] = Point(hitRect.getMaxX(), hitRect.getMaxY());
	point1[2] = Point(hitRect.getMaxX(), hitRect.getMinY());
	point1[3] = Point(hitRect.getMinX(), hitRect.getMinY());
	draw->drawPolygon(point1, 4, Color4F(1,0,0,0), 1, Color4F(1,0,0,1));*/

	born();
}

void Dog::execute()
{
	//产生子弹
	if (bulletDelay <= 0 && isReady)
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

void Dog::displayExplode()
{
	log("Dog creash !!", getID());
	this->stopAllActions();
	body->stopAllActions();
	isReady = false;
	explode->setVisible(true);
	explode->runAction(actions);
}

void Dog::distroy()
{
	body->setVisible(false);
	explode->setVisible(false);
	explode->stopAllActions();

	log("Dog %d Crashed!!", id);
	born();
	//NotificationCenter::getInstance()->postNotification("test", NULL);
}

void Dog::born()
{
	//reset
	body->setVisible(true);
	body->runAction(bodyAct);
	explode->setVisible(false);
	isReady = true;
	Size visualSize = Director::getInstance()->getVisibleSize();
	this->setPosition(random(100.0f, visualSize.width - 100), random(visualSize.height + 50, visualSize.height + 500));
	move();
}

void Dog::move()
{
	Size visualSize = Director::getInstance()->getVisibleSize();
	int type = random(0, 1);
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(this->getPositionX() - 400, 330);
	bezier1.controlPoint_2 = Point(this->getPositionX() + 400, 280);
	bezier1.endPosition = Point(random(0.0f, visualSize.width), random(700.0f, visualSize.height));
	BezierTo* bezierTo1 = BezierTo::create(6.0f, bezier1);

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(this->getPositionX() + 400, 330);
	bezier2.controlPoint_2 = Point(this->getPositionX() - 400, 280);
	bezier2.endPosition = Point(random(0.0f, visualSize.width), random(700.0f, visualSize.height));
	BezierTo* bezierTo2 = BezierTo::create(6.0f, bezier2);

	MoveTo* moveTo = MoveTo::create(6, Point(random(0.0f, visualSize.width), random(700.0f, visualSize.height)));

	CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(Dog::move, this));
	Sequence* seq;
	switch (type)
	{
	case 0:
	{
		seq = Sequence::create(bezierTo1, callfunc, NULL);
	}
		break;
	case 1:
	{
		seq = Sequence::create(bezierTo2, callfunc, NULL);
	}
		break;
	case 2:
	{
		seq = Sequence::create(moveTo, callfunc, NULL);
	}
		break;
	}
	this->runAction(seq);
}

void Dog::hitCat(Cat* cat)
{
	//是否砸到猫
	if (cat->getReady() == false)
	{
		return;
	}
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		TubeBullet* temp = it->second;
		Rect temp1 = Rect(temp->getPositionX() - temp->getHitRect().size.width / 2,
			temp->getPositionY() - temp->getHitRect().size.height / 2,
			temp->getHitRect().size.width, temp->getHitRect().size.height);

		Rect temp2 = Rect(cat->getPositionX() - cat->getHitRect().size.width / 2,
			cat->getPositionY() - cat->getHitRect().size.height / 2,
			cat->getHitRect().size.width, cat->getHitRect().size.height);

		if (temp1.intersectsRect(temp2))
		{
			log("Dog Hit:: { %d }", it->second->getID());
			TubeBullet* temp = bullets.at(it->first);
			auto parent = temp->getParent();
			if (parent != NULL)
			{
				parent->removeChild(temp, true);
			}
			//猫咪爆炸
			cat->displayExplode();
			NotificationCenter::getInstance()->postNotification("HitCat");
			//下一个迭代器定位的元素位置
			it = bullets.erase(it);
		}
		else
		{
			it++;
		}
	}
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

bool Dog::getReady()
{
	return isReady;
}
