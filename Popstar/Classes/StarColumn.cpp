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

