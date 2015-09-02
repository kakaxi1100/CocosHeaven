#include "GameData.h"

int GameData::mIncrementID = 0;

int GameData::getAvailableID()
{
	return ++mIncrementID;
}