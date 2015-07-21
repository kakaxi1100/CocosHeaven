#include "StarMatrix.h"

bool StarMatrix::init()
{
	if (!Node::init())
	{
		return false;
	}

	for (size_t i = 0; i < COLS; i++)
	{
		StarColumn* starColumn = StarColumn::create();
		for (size_t j = 0; j < ROWS; j++)
		{
			int type = random(1, 5);
			log("%d Row %d Col tile type is %d", j, i, type);
			Star* temp = Star::create(type);
			const Size& s = temp->getContentSize();
			temp->newRow = temp->row = j;
			temp->newCol = temp->col = i;
			temp->setPosition(i*s.width + s.width / 2, j * s.height + s.height / 2);
			starColumn->pushStar(temp);
			addChild(temp);
		}
		matrix.insert(i, starColumn);
	}

	if (matrix.find(0) != matrix.end())
	{
		auto p = matrix.at(0);
		if (p->getSize() > 0)
		{
			const Size& t = p->getStarByIndex(0)->getContentSize();
			starH = t.height;
			starW = t.width;
		}
		else
		{
			log("No Star!");
			return false;
		}
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StarMatrix::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool StarMatrix::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	pos = this->convertToNodeSpace(pos);
	int r = getRow(pos.y);
	int c = getCol(pos.x);
	log("Select Row %d, Col %d", r, c);

	if (matrix.find(c) == matrix.end())//假如没有找到此列
	{
		return false;
	}
	else
	{
		if (matrix.at(c)->getStarByIndex(r) == NULL)//假如没有找到此星星
		{
			return false;
		}
	}

	//取得找到的星星

	Star* temp= matrix.at(c)->getStarByIndex(r);
	if (temp->getIsAvctive() == false)
	{
		setAllStarToNormal();
		checkSameStar(temp->type, temp->row, temp->col);
	}
	else//否则消除当前选中的方块
	{

	}
	return true;
}

void StarMatrix::popStars()
{
	//检查每列
	for (auto p : matrix)
	{
		auto sc = p.second;
		for (size_t i = 0; i < sc->getSize(); i++)
		{
			if (sc->getStarByIndex(i)->getIsAvctive() == true)
			{

			}
		}
	}
}

void StarMatrix::checkSameStar(int type, int row, int col)
{
	log("Check : Row %d, Col %d", row, col);
	//退出条件
	//1、是否在框内、是否有此列
	if (row >= ROWS || row < 0 || col >= COLS || col < 0 || matrix.find(col) == matrix.end())
	{
		return;
	}
	//2、是否有星星，是否符合选中条件
	Star* s = matrix.at(col)->getStarByIndex(row);
	if (s == NULL || s->getIsAvctive() == true || s->type != type)
	{
		return;
	}

	s->setIsActive(true);

	//先检测向上的点
	checkSameStar(type, row + 1, col);
	//再检测向下的点
	checkSameStar(type, row - 1, col);
	//然后检测向左的点
	checkSameStar(type, row, col - 1);
	//最后检测向右的点
	checkSameStar(type, row, col + 1);
}

void StarMatrix::setAllStarToNormal()
{
	for (auto p : matrix)
	{
		auto sc = p.second;
		for (size_t i = 0; i < sc->getSize(); i++)
		{
			auto s = sc->getStarByIndex(i);
			if (s->getIsAvctive() == true)
			{
				s->setIsActive(false);
			}
		}
	}
}

int StarMatrix::getRow(float y)
{
	return static_cast<int>(y/starH);
}

int StarMatrix::getCol(float x)
{
	return static_cast<int>(x/starW);
}
