#pragma once

class IBullet 
{
public:
	virtual void setID(int value) = 0;
	virtual int getID() = 0;
	virtual void excute() = 0;
	virtual void bulletRelease() = 0;
};

