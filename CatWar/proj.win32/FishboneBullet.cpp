#include "FishboneBullet.h"

bool FishboneBullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void FishboneBullet::excute()
{
	log("biubiubiubiubiubiubiuibu~~~");
	//throw std::logic_error("The method or operation is not implemented.");
}

int FishboneBullet::getID()
{
	return id;
}

void FishboneBullet::setID(int value)
{
	id = value;
}