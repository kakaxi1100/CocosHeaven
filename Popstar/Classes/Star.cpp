#include "Star.h"

Star* Star::create(int pType)
{
	Star *pRet = new(std::nothrow) Star();
	if (pRet && pRet->init(pType))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Star::init(int pType)
{
	if (!Sprite::init())
	{
		return false;
	}

	type = pType;
	col = 0;
	row = 0;
	/*switch (type)
	{
	case 1:
		setTexture("blue.png");
		break;
	case 2:
		setTexture("green.png");
		break;
	case 3:
		setTexture("orange.png");
		break;
	case 4:
		setTexture("purple.png");
		break;
	case 5:
		setTexture("red.png");
		break;
	default:
		break;
		}*/
	/*
	//用 string 存，然后setTexture，初始化的时候，会报错，什么鬼！！
	switch (type)
	{
	case 1:
		normalPNG = "blue.png";
		selectPNG = "blue_heart.png";
		break;
	case 2:
		normalPNG = "green.png";
		selectPNG = "green_heart.png";
		break;
	case 3:
		normalPNG = "orange.png";
		selectPNG = "orange_heart.png";
		break;
	case 4:
		normalPNG = "purple.png";
		selectPNG = "purple_heart.png";
		break;
	case 5:
		normalPNG = "red.png";
		selectPNG = "red_heart.png";
		break;
	default:
		break;
	}*/
	//不能保存多个spriteframe 来达到切换图片的目的，因为当你设置另一个frame的时候，sprite 的引用已经没有了。会报错
	/*normal = SpriteFrame::create(normalPNG, Rect(0, 0, 48, 48));
	select = SpriteFrame::create(selectPNG, Rect(0, 0, 64, 64));
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFrame(normal, "normal");
	cache->addSpriteFrame(select, "select");*/

	//没必要用TexttureCache 缓存，因为setTexture会添加到TextureCache中
	//auto cache = TextureCache::getInstance();

	//cache->addImage(normalPNG);
	//cache->addImage(selectPNG);

	setIsActive(false);
	//setTexture("red_heart.png");
	//setTexture("red.png");
	//setIsActive(true);
	//this->scheduleUpdate();

	return true;
}
void Star::setIsActive(bool value)
{
	mIsActive = value;
	if (mIsActive == false)
	{
		switch (type)
		{
		case 1:
			setTexture("blue.png");
			break;
		case 2:
			setTexture("green.png");
			break;
		case 3:
			setTexture("orange.png");
			break;
		case 4:
			setTexture("purple.png");
			break;
		case 5:
			setTexture("red.png");
			break;
		default:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case 1:
			setTexture("blue_heart.png");
			break;
		case 2:
			setTexture("green_heart.png");
			break;
		case 3:
			setTexture("orange_heart.png");
			break;
		case 4:
			setTexture("purple_heart.png");
			break;
		case 5:
			setTexture("red_heart.png");
			break;
		default:
			break;
		}
	}
}

/*
void Star::setIsActive(bool value)
{
	mIsActive = value;
	if (mIsActive == false)
	{
		this->setDisplayFrame(normal);
	}
	else
	{
		this->setDisplayFrame(select);
	}
}*/

bool Star::getIsAvctive()
{
	return mIsActive;
}


void Star::destroy()
{
	if (this->getParent() != NULL)
	{
		this->getParent()->removeChild(this, true);
	}
}

void Star::moveStar()
{
	if (col != newCol || row != newRow)
	{
		auto size = this->getContentSize();
		float posX = newCol*size.width + size.width / 2;
		float posY = newRow * size.height + size.height / 2;
		//setPosition(posX, posY);
		MoveTo* moveTo = MoveTo::create(0.3, Point(posX, posY));
		this->runAction(moveTo);

		col = newCol;
		row = newRow;
	}
}

void Star::update(float dt)
{
	mIsActive ^= 1;
	setIsActive(mIsActive);
}