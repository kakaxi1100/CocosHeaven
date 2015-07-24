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
	delay = -1;
	isMoveRowOver = isMoveColOver = false;

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
	}

	setIsActive(false);

	this->scheduleUpdate();

	return true;
}
void Star::setIsActive(bool value)
{
	mIsActive = value;
	if (mIsActive == false)
	{
		setTexture(normalPNG);
	}
	else
	{
		setTexture(selectPNG);
	}
}

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
	this->schedule(schedule_selector(Star::moveRow));
	this->schedule(schedule_selector(Star::moveCol));
}

void Star::moveRow(float dt)
{
	
}
void Star::moveCol(float dt)
{

}

/*void Star::moveStar()
{
	if (col != newCol || row != newRow)
	{
		auto size = this->getContentSize();
		float posX = newCol*size.width + size.width / 2;
		float posY = newRow * size.height + size.height / 2;
		//setPosition(posX, posY);
		MoveTo* moveTo = MoveTo::create(0.3f, Point(posX, posY));
		this->runAction(moveTo);

		col = newCol;
		row = newRow;
	}
}
*/
void Star::jumpStar()
{
	auto jump = JumpBy::create(0.1f, Point(0,0), 5, 1);

	this->runAction(jump);
}

void Star::dropStar()
{
	auto size = this->getContentSize();
	auto p = this->getPosition();
	
	p.y -= this->speedY;
	if (p.y < getStartPos().y)
	{
		p.y = getStartPos().y;
		this->unscheduleUpdate();
	}
	setPosition(p.x, p.y);
}

void Star::update(float dt)
{
	if (delay == 0)
	{
		dropStar();
	}
	else
	{
		delay--;
	}
}

const Vec2& Star::getStartPos()
{
	auto size = this->getContentSize();

	return Vec2(col*size.width + size.width / 2, row*size.height + size.height / 2);
}