#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	StarMatrix* s = StarMatrix::create();
	addChild(s);

	return true;
}