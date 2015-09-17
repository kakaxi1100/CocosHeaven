#include "UILayer.h"

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite* scoreTxt = Sprite::create("");

	return true;
}
