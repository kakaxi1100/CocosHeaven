#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class FloatWord :
	public Node
{
public:
	static FloatWord* create(const string& word, const int fontSize, Point begin);
	bool init(const std::string& word, const int fontSize, Point begin);
	void floatIn(const float delay, function<void()> callback);
	void floatOut(const float delay, function<void()> callback);
	void floatInOut(const float speed, const float delay, function<void()> callback);

private:
	int _fontSize;
	Point _begin;
	Label* _label;
};

