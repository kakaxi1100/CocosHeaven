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
	//�� string �棬Ȼ��setTexture����ʼ����ʱ�򣬻ᱨ��ʲô����
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
	//���ܱ�����spriteframe ���ﵽ�л�ͼƬ��Ŀ�ģ���Ϊ����������һ��frame��ʱ��sprite �������Ѿ�û���ˡ��ᱨ��
	/*normal = SpriteFrame::create(normalPNG, Rect(0, 0, 48, 48));
	select = SpriteFrame::create(selectPNG, Rect(0, 0, 64, 64));
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFrame(normal, "normal");
	cache->addSpriteFrame(select, "select");*/

	//û��Ҫ��TexttureCache ���棬��ΪsetTexture����ӵ�TextureCache��
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