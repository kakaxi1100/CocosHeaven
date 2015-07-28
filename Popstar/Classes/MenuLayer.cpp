#include "MenuLayer.h"

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visiableSize = Director::getInstance()->getVisibleSize();

	//1¡¢Ìí¼Ó±³¾°Í¼Æ¬
	Sprite* menuBG = Sprite::create("bg_menuscene.jpg");
	menuBG->setPosition(visiableSize.width / 2, visiableSize.height / 2);
	this->addChild(menuBG);
	//2¡¢Ìí¼Ó²Ëµ¥À¸
	MenuItemImage* startMI = MenuItemImage::create("menu_start.png", "menu_start.png",CC_CALLBACK_0(MenuLayer::startGame, this));

	Menu* menu = Menu::create(startMI, NULL);
	menu->alignItemsVertically();
	menu->setPosition(visiableSize.width/2, visiableSize.height/2);
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame()
{
	Director::getInstance()->replaceScene(GameScene::create());
}

