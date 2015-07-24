#include "StarColumn.h"

bool StarColumn::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void StarColumn::onExit()
{
	Node::onExit();

	colStars.clear();

	log("StarColumn Exit!!");
}

void StarColumn::pushStar(Star* s)
{
	colStars.pushBack(s);
}

size_t StarColumn::getSize()
{
	return colStars.size();
}

Star* StarColumn::getStarByIndex(int i)
{
	if (colStars.size() <= i)
	{
		return NULL;
	}

	return colStars.at(i);
}

bool StarColumn::eraseStar(Star* s)
{
	colStars.eraseObject(s, false);
	changeStarsRow();
	return true;
}

bool StarColumn::eraseStarByIndex(int i)
{
	colStars.erase(i);
	changeStarsRow();
	return true;
}

void StarColumn::changeStarsRow()
{
	for (int i = 0; i < colStars.size(); i++)
	{
		auto s = getStarByIndex(i);
		if (s != NULL)
		{
			s->newRow = i;
		}
	}
}

void StarColumn::changeStarsCol()
{
	for (int i = 0; i < colStars.size(); i++)
	{
		auto s = getStarByIndex(i);
		if (s != NULL)
		{
			s->newCol = mColNum;
		}
	}
}

void StarColumn::setColNum(int value)
{
	mColNum = value;
	changeStarsCol();
}

int StarColumn::getColNum()
{
	return mColNum;
}