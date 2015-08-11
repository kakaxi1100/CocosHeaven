#include "Dog.h"

bool Dog::init()
{
	if (!Node::init())
	{
		return false;
	}

	display();

	return true;
}

void Dog::display()
{
	//body
	Sprite* body = Sprite::create("DrDog1.png");
	
	Animation* bodyAni = Animation::create();
	bodyAni->addSpriteFrameWithFile("DrDog1.png");
	bodyAni->addSpriteFrameWithFile("DrDog2.png");
	bodyAni->setLoops(-1);
	bodyAni->setDelayPerUnit(0.1f);

	Animate* bodyAct = Animate::create(bodyAni);

}