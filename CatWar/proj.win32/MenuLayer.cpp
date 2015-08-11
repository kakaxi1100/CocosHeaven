#include "MenuLayer.h"

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visualSize = Director::getInstance()->getVisibleSize();
	log("{ %f , %f }", visualSize.width, visualSize.height);
	Sprite* menuBG = Sprite::create("bg.png");
	addChild(menuBG);

	Sprite* title1 = Sprite::create("meowstar.png");
	title1->setPosition(0, (this->getContentSize().height - title1->getContentSize().height)/2);
	addChild(title1);

	Sprite* title2 = Sprite::create("battle.png");
	title2->setPosition(title1->getPositionX(), title1->getPositionY() - title1->getContentSize().height/2);
	addChild(title2);

	MenuItemImage* mNew = MenuItemImage::create("newgameA.png", "newgameB.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	MenuItemImage* mContiue = MenuItemImage::create("continueA.png", "continueB.png");
	MenuItemImage* mAbout = MenuItemImage::create("aboutA.png","aboutB.png");

	Menu* m = Menu::create();
	m->setPosition(Vec2::ZERO);
	m->addChild(mNew);
	m->addChild(mContiue);
	m->addChild(mAbout);
	m->alignItemsVerticallyWithPadding(50);
	addChild(m);

	//log("{ %f , %f }", this->getBoundingBox().size.width, this->getBoundingBox().size.height);

	return true;
}

void MenuLayer::startGame()
{
	log("Game Started!");
	Director::getInstance()->replaceScene(GameScene::create());
}