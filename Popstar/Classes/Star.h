#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Star
	: public Sprite
{
public:
	bool init(int pType);	
	static Star* create(int pType);

	int type;

	int col;
	int row;

	int newCol;
	int newRow;

	//�������ƶ���Ч����
	float speedX;
	float speedY;
	float aX;
	float aY;

	void setIsActive(bool value);
	bool getIsAvctive();

	void update(float dt);
	int delay;//����ʱ�ӳٶ����뿪ʼ��

	void starEnter();
	void destroy();
	void moveStar();
	void jumpStar();
	//����������ʱ�ƶ�����
	void moveRow(float dt);
	void moveCol(float dt);

	bool isMoveRow;
	bool isMoveCol;
private:
	bool mIsActive;
	
	//��������������
	const Vec2& getStartPos();
	void dropStar();
	
	float destY;
	float destX;

	std::string normalPNG;
	std::string selectPNG;
};