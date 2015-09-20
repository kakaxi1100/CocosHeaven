#pragma once
#include "../cocos2d.h"

USING_NS_CC;

class UILayer :
	public Layer
{
public:
	CREATE_FUNC(UILayer);

	virtual bool init();
	virtual void onExit();
private:
	Node* score;
	int life;
	int scoreNum;
	Vector<Sprite*> lifes;
	void cutLife(Ref * data);
	void addScore(Ref* data);
};

