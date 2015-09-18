#include "UILayer.h"

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	life = 1;

	Size visualSize = Director::getInstance()->getVisibleSize();

	Node* score = Node::create();
	score->setPosition(visualSize.width - 130, visualSize.height - 60);
	addChild(score);
	Sprite* scoreTxt = Sprite::create("score.png");
	scoreTxt->setPosition(-50, 0);
	score->addChild(scoreTxt);
	//对应的 ascii 码表
	//图片的排版是 1234567890 起始字符是 1 
	//那么最后一个 0 对应的字符就是 9 的下一个 ascii 码 即 ':'
	Label* scoreValue = Label::createWithCharMap("shu.png",26,31, '1');
	//1=49 9=57 ：=58
	scoreValue->setString("::::");
	scoreValue->setPosition(54, 0);
	score->addChild(scoreValue);


	Node* lifesCan = Node::create();
	lifesCan->setPosition(50, visualSize.height - 60);
	addChild(lifesCan);

	for (int i = 0; i < life; i++)
	{
		Sprite* life = Sprite::create("cat.png");
		life->setScale(0.5);
		lifes.pushBack(life);
		life->setPositionX(i*70);
		lifesCan->addChild(life);
	}

	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(UILayer::cutLife), "HitCat",NULL);

	return true;
}

void UILayer::onExit()
{
	Layer::onExit();
	NotificationCenter::getInstance()->removeAllObservers(this);
}

void UILayer::cutLife(Ref* data)
{
	if (life > 0) {
	lifes.at((life--) - 1)->setVisible(false);
	if (life == 0)
	{
		NotificationCenter::getInstance()->postNotification("GameOver");
	}
}
}
