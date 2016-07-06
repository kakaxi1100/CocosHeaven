#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
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
	mSoundOn = MenuItemImage::create("sound-on-A.png", "sound-on-B.png" ,
		CC_CALLBACK_1(MenuLayer::openSound, this));
	std::function<void(Ref*)> f = 
		[&](Ref*)->void{mSoundOn->setVisible(true);
						mSoundOff->setVisible(false); 
						CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); };
	mSoundOff = MenuItemImage::create("sound-off-A.png", "sound-off-B.png",f);

	Menu* sound = Menu::create(mSoundOff, mSoundOn, NULL);
	sound->setPosition(-220, -300);
	addChild(sound);

	return true;
}


void MenuLayer::startGame()
{
	log("Game Started!");
	Director::getInstance()->replaceScene(GameScene::create());
}

void MenuLayer::openSound(Ref* data)
{
	mSoundOn->setVisible(false);
	mSoundOff->setVisible(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
