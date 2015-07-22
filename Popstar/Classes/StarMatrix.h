#pragma once 

#include "cocos2d.h"

#include "Star.h"
#include "StarColumn.h"
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
	bool onTouchBegan(Touch* touch, Event* event);
private:
	//Map<int, StarColumn*> matrix;
	Vector<StarColumn*> matrix;
	int getRow(float x);
	int getCol(float y);

	void checkSameStar(int type, int row, int col);
	void popStars();
	void moveStars();
	void setAllStarToNormal();

	int starW;
	int starH;

	int popStarCount;
};