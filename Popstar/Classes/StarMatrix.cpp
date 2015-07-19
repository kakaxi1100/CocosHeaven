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

	//�����ҵ�0_0
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
	//����û���ҵ�����
	if (matrix.find(key) == matrix.end())
	{
		return false;//����false ���ܴ����Ժ���¼������� �ƶ���� ̧������
	}

	Star* temp = matrix.at(key);
	//����ж��ٸ���ͬ�����ǣ�Ҫͬʱ����ѡ��״̬
	checkSameStar(temp->type, temp->row, temp->col);
	return true;
}

void StarMatrix::checkSameStar(int type, int row, int col)
{
	//�õݹ�����
	log("Check :  Row %d, Col %d", row, col);
	//�˳�����
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
	//�ȼ�����ϵĵ�
	checkSameStar(type, row + 1, col);
	//�ټ�����µĵ�
	checkSameStar(type, row - 1, col);
	//Ȼ��������ĵ�
	checkSameStar(type, row, col - 1);
	//��������ҵĵ�
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
