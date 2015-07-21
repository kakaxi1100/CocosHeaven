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

	if (matrix.find(c) == matrix.end())//����û���ҵ�����
	{
		return false;
	}
	else
	{
		if (matrix.at(c)->getStarByIndex(r) == NULL)//����û���ҵ�������
		{
			return false;
		}
	}

	//ȡ���ҵ�������

	Star* temp= matrix.at(c)->getStarByIndex(r);
	if (temp->getIsAvctive() == false)
	{
		setAllStarToNormal();
		checkSameStar(temp->type, temp->row, temp->col);
	}
	else//����������ǰѡ�еķ���
	{

	}
	return true;
}

void StarMatrix::popStars()
{
	//���ÿ��
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
	//�˳�����
	//1���Ƿ��ڿ��ڡ��Ƿ��д���
	if (row >= ROWS || row < 0 || col >= COLS || col < 0 || matrix.find(col) == matrix.end())
	{
		return;
	}
	//2���Ƿ������ǣ��Ƿ����ѡ������
	Star* s = matrix.at(col)->getStarByIndex(row);
	if (s == NULL || s->getIsAvctive() == true || s->type != type)
	{
		return;
	}

	s->setIsActive(true);

	//�ȼ�����ϵĵ�
	checkSameStar(type, row + 1, col);
	//�ټ�����µĵ�
	checkSameStar(type, row - 1, col);
	//Ȼ��������ĵ�
	checkSameStar(type, row, col - 1);
	//��������ҵĵ�
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
