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

	float speedX;
	float speedY;

	void setIsActive(bool value);
	bool getIsAvctive();

	void update(float dt);
	int delay;//����ʱ�ӳٶ����뿪ʼ��

	void destroy();
	void moveStar();
	void jumpStar();
private:
	bool mIsActive;
	
	//��������������
	const Vec2& getStartPos();
	void dropStar();
	
	//����������ʱ�ƶ�����
	void moveRow(float dt);
	void moveCol(float dt);
	bool isMoveRowOver;
	bool isMoveColOver;

	std::string normalPNG;
	std::string selectPNG;
};