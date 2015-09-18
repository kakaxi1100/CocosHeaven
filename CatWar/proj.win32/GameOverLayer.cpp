#include "GameOverLayer.h"
#include "MenuScene.h"

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite* overTxt = Sprite::create("gameover.png");
	overTxt->setPosition(this->getContentSize().width/2, this->getContentSize().height/2 + 150);
	addChild(overTxt);

	MenuItemImage* menuItem = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_0(GameOverLayer::backToMenu, this));

	Menu* menu = Menu::create(menuItem, NULL);
	addChild(menu);

	return true;
}

void GameOverLayer::backToMenu()
{
	Director::getInstance()->replaceScene(MenuScene::create());
}
