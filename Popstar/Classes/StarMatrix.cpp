#include "StarMatrix.h"

bool StarMatrix::init()
{
	if (!Node::init())
	{
		return false;
	}

	for (size_t i = 0; i < ROWS; i++)
	{
		for (size_t j = 0; j < COLS; j++)
		{
			int type = random(1, 5);
			log("%d Row %d Col tile type is %d", i, j, type);
			Star* temp = Star::create(type);
			const Size& s = temp->getContentSize();
			temp->row = i;
			temp->col = j;
			temp->setPosition(j*s.width + s.width / 2, i * s.height + s.height / 2);
			addChild(temp);
			matrix.insert(Value(static_cast<int>(i)).asString() + "_" + Value(static_cast<int>(j)).asString(), temp);
		}
	}

	//假如找到0_0
	if (matrix.find("0_0") != matrix.end())
	{
		const Size& t = matrix.at("0_0")->getContentSize();
		starH = t.height;
		starW = t.width;
	}
	else{
		log("No Star!");
		return false;
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
	std::string key = Value(r).asString() + "_" + Value(c).asString();
	//假如没有找到星星
	if (matrix.find(key) == matrix.end())
	{
		return false;//返回false 则不能触发以后的事件，比如 移动鼠标 抬起鼠标等
	}

	Star* temp = matrix.at(key);
	//检测有多少个相同的星星，要同时处于选中状态
	checkSameStar(temp->type, temp->row, temp->col);
	return true;
}

void StarMatrix::checkSameStar(int type, int row, int col)
{
	//用递归来做
	log("Check :  Row %d, Col %d", row, col);
	//退出条件
	if (row >= ROWS || row < 0 || col >= COLS || col < 0)
	{
		return;
	}

	auto it = matrix.find(Value(row).asString() + "_" + Value(col).asString());
	auto s = it->second;
	if (it == matrix.end() || s->getIsAvctive() == true || s->type != type)
	{
		return;
	}
	else
	{
		s->setIsActive(true);
	}
	//先检测向上的点
	checkSameStar(type, row + 1, col);
	//再检测向下的点
	checkSameStar(type, row - 1, col);
	//然后检测向左的点
	checkSameStar(type, row, col - 1);
	//最后检测向右的点
	checkSameStar(type, row, col + 1);
}

int StarMatrix::getRow(float y)
{
	return static_cast<int>(y/starH);
}

int StarMatrix::getCol(float x)
{
	return static_cast<int>(x/starW);
}
