#include "StarMatrix.h"

bool StarMatrix::init()
{
	if (!Node::init())
	{
		return false;
	}

	if (!gameAgain())
	{
		return false;
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StarMatrix::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

bool StarMatrix::gameAgain()
{
	starH = starW = 0;
	startMoveRow = startMoveCol = false;
	isCheckOver = false;
	matrix.clear();
	selectStar.clear();

	removeAllChildren();
	//初始化
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
			//用来做进场动画
			temp->delay = j * 30 + i*random(0, 5);
			//temp->setPosition(i*s.width + s.width / 2, j * s.height + s.height / 2);
			temp->setPosition(convertToWindowSpace(Point(i*s.width + s.width / 2, -s.height / 2)));
			starColumn->pushStar(temp);
			starColumn->setColNum(i);
			addChild(temp);
			temp->starEnter();
		}
		matrix.pushBack(starColumn);
	}

	if (matrix.size() > 0)
	{
		auto sc = matrix.at(0);
		if (sc->getSize() > 0)
		{
			const Size& t = sc->getStarByIndex(0)->getContentSize();
			starH = t.height;
			starW = t.width;
		}
		else
		{
			log("No Star!");
			return false;
		}
	}
	return true;
}


bool StarMatrix::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	pos = this->convertToNodeSpace(pos);
	int r = getRow(pos.y);
	int c = getCol(pos.x);
	log("Select Row %d, Col %d", r, c);

	if (matrix.size() < c + 1)//假如没有找到此列
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
		setSelectStarToNormal();
		selectStar.clear();
		checkSameStar(temp->type, temp->row, temp->col);
		//让选中的星星跳一下
		for (auto s : selectStar)
		{
			s->jumpStar();
		}
	}
	else//否则消除当前选中的方块re
	{
		if (selectStar.size() > 1)
		{
			popStars();
			//开始消除星星
			for (auto s : selectStar)
			{
				s->destroy();
				//selectStar.eraseObject(s);
			}
			selectStar.clear();
			startToMove();
		}
	}
	return true;
}

//每个星星都有个新的坐标，为播放移动动画做准备
void StarMatrix::popStars()
{
	//检查每列
	for (int i = 0; i < matrix.size(); i++)
	{
		auto sc = matrix.at(i);
		//检查每行
		for (size_t j = 0; j < sc->getSize(); j++)
		{
			auto s = sc->getStarByIndex(j);
			if (s->getIsAvctive() == true)
			{
				sc->eraseStarByIndex(j);
				j--;
			}
		}

		//再检查每列
		if (sc->getSize() == 0)
		{
			matrix.eraseObject(sc);//注意matrix.size改变了，对应的列也改变了
			i--;
			//更改每列的列值
			for (int k = 0; k < matrix.size(); k++)
			{
				matrix.at(k)->setColNum(k);
			}
		}
	}
}
void StarMatrix::startToMove()
{
	for (auto sc : matrix)
	{
		for (size_t i = 0; i < sc->getSize(); i++)
		{
			auto s = sc->getStarByIndex(i);
			s->moveStar();
		}
	}

	startMoveRow = true;
	startMoveCol = false;
}

void StarMatrix::moveStarsRow()
{
	if (startMoveRow == true)
	{
		startMoveCol = true;
		for (auto sc : matrix)
		{
			for (size_t i = 0; i < sc->getSize(); i++)
			{
				auto s = sc->getStarByIndex(i);
				if (s->isMoveRow == true)
				{
					startMoveCol = false;
					s->moveRow(0);
				}
			}
		}
		if (startMoveCol == true)
		{
			startMoveRow = false;
		}
	}
}

void StarMatrix::moveStarsCol()
{
	if (startMoveCol == true)
	{
		bool over = true;
		for (auto sc : matrix)
		{
			for (size_t i = 0; i < sc->getSize(); i++)
			{
				auto s = sc->getStarByIndex(i);
				if (s->isMoveCol == true)
				{
					over = false;
					s->moveCol(0);
				}
			}
		}
		if (over == true)
		{
			startMoveRow = startMoveCol = false;
			isCheckOver = true;
		}
	}
}

void StarMatrix::checkSameStar(int type, int row, int col)
{
	log("Check : Row %d, Col %d", row, col);
	//退出条件
	//1、是否在框内、是否有此列
	if (row >= ROWS || row < 0 || col >= COLS || col < 0 || matrix.size() < col + 1)
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
	selectStar.pushBack(s);

	//先检测向上的点
	checkSameStar(type, row + 1, col);
	//再检测向下的点
	checkSameStar(type, row - 1, col);
	//然后检测向左的点
	checkSameStar(type, row, col - 1);
	//最后检测向右的点
	checkSameStar(type, row, col + 1);
}

void StarMatrix::setSelectStarToNormal()
{
	for (auto s : selectStar)
	{
		s->setIsActive(false);
	}
	for (auto sc : matrix)
	{
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

bool StarMatrix::checkOver()
{
	for (ssize_t i = 0; i < matrix.size(); i++)
	{
		auto sc = matrix.at(i);
		for (size_t j = 0; j < sc->getSize(); j++)
		{
			auto s = sc->getStarByIndex(j);
			size_t  tempj = j;
			tempj++;
			//检查上边
			if (sc->getSize() > tempj)
			{
				auto temps = sc->getStarByIndex(tempj);
				if (s->type == temps->type)
				{
					return false;
				}
			}
			//检查右边
			ssize_t tempi = i;
			tempi++;
			if (matrix.size() > tempi)
			{
				auto tempsc = matrix.at(tempi);
				if (sc->getSize() > tempj)
				{
					auto temps = sc->getStarByIndex(tempj);
					if (s->type == temps->type)
					{
						return false;
					}
				}
			}
		}
	}
	log("Game Over!");
	return true;
}

void StarMatrix::update(float dt)
{
	moveStarsRow();
	moveStarsCol();

	if (isCheckOver == true)
	{ 
		isCheckOver = false;
		if (checkOver())
		{
			gameAgain();
		}
	}
}