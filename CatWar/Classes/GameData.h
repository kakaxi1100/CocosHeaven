#pragma once

//需要全局访问的数据
class GameData
{
public:
	static int getAvailableID();
private:
	static int mIncrementID;

};