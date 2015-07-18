#pragma once 

#include "cocos2d.h"

#include "Star.h"
#include "PathNode.h"

USING_NS_CC;

#define ROWS 10
#define COLS 10

class StarMatrix
	:public Node
{
public:
	virtual bool init();
	CREATE_FUNC(StarMatrix);

	Map<std::string, Star*> matrix;
	bool onTouchBegan(Touch* touch, Event* event);
	int getRow(float x);
	int getCol(float y);

	void checkSameStar(int type, int row, int col);

	int starW;
	int starH;
};