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
	void update(float dt);
private:
	Vector<StarColumn*> matrix;

	Vector<Star*> selectStar;

	int getRow(float x);
	int getCol(float y);

	void checkSameStar(int type, int row, int col);
	void popStars();
	void moveStarsRow();
	void moveStarsCol();
	void startToMove();
	void setSelectStarToNormal();

	bool checkOver();
	bool gameAgain();

	bool startMoveRow;
	bool startMoveCol;
	bool isCheckOver;

	int starW;
	int starH;
};