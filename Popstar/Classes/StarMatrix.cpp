#include "StarMatrix.h"

bool StarMatrix::init()
{
	if (!Node::init())
	{
		return false;
	}

	starH = starW = 0;

	//��ʼ��
	for (size_t i = 0; i < COLS; i++)
	{
		StarColumn* starColumn = StarColumn::create();
		for (size_t j = 0; j < ROWS; j++)
		{
			int type;
			if (i != 5)
			{
				type = random(1, 5);
			}
			else{
				type = 1;
			}
			log("%d Row %d Col tile type is %d", j, i, type);
			Star* temp = Star::create(type);
			const Size& s = temp->getContentSize();
			temp->newRow = temp->row = j;
			temp->newCol =temp->col = i;
			//��������������
			//temp->setPosition(i*s.width + s.width / 2, j * s.height + s.height / 2);
			temp->setPosition(convertToWindowSpace(Point(i*s.width + s.width / 2, s.height / 2)));
			starColumn->pushStar(temp);
			starColumn->setColNum(i);
			addChild(temp);
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

	if (matrix.size() < c + 1)//����û���ҵ�����
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
		selectStar.clear();
		setAllStarToNormal();
		checkSameStar(temp->type, temp->row, temp->col);
		//��ѡ�е�������һ��
		for (auto s : selectStar)
		{
			s->jumpStar();
		}
	}
	else//����������ǰѡ�еķ���re
	{
		if (selectStar.size() > 1)
		{
			popStars();
			moveStars();
		}
	}
	return true;
}

//ÿ�����Ƕ��и��µ����꣬Ϊ�����ƶ�������׼��
void StarMatrix::popStars()
{
	//���ÿ��
	for (int i = 0; i < matrix.size(); i++)
	{
		auto sc = matrix.at(i);
		//���ÿ��
		for (size_t j = 0; j < sc->getSize(); j++)
		{
			auto s = sc->getStarByIndex(j);
			if (s->getIsAvctive() == true)
			{
				//ɾ��Ҫ����������
				s->destroy();
				sc->eraseStarByIndex(j);
				j--;
			}
		}

		//�ټ��ÿ��
		if (sc->getSize() == 0)
		{
			matrix.eraseObject(sc);//ע��matrix.size�ı��ˣ���Ӧ����Ҳ�ı���
			i--;
			//����ÿ�е���ֵ
			for (int k = 0; k < matrix.size(); k++)
			{
				matrix.at(k)->setColNum(k);
			}
		}
	}
}

void StarMatrix::moveStars()
{
	for (auto sc : matrix)
	{
		for (size_t i = 0; i < sc->getSize(); i++)
		{
			auto s =  sc->getStarByIndex(i);
			s->moveStar();
		}
	}
}

void StarMatrix::checkSameStar(int type, int row, int col)
{
	log("Check : Row %d, Col %d", row, col);
	//�˳�����
	//1���Ƿ��ڿ��ڡ��Ƿ��д���
	if (row >= ROWS || row < 0 || col >= COLS || col < 0 || matrix.size() < col + 1)
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
	selectStar.pushBack(s);

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