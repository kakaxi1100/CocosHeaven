#include "BulletManager.h"

int BulletManager::validID = 0;
unordered_map<int, IBullet*> BulletManager::bulletsMap;

void BulletManager::addBullet(int type)
{
	IBullet* pBullet = NULL;

	switch (type)
	{
	case 1:
	{
		FishboneBullet* fishbone = FishboneBullet::create();
		//GameScene::getGameLayer()->addChild(fishbone);
		pBullet = fishbone;//static_cast<FishboneBullet*>(FishboneBullet::create());
		fishbone->retain();
	}
		break;
	default:
		break;
	}

	if (pBullet != nullptr)
	{
		int tempID = ++validID;
		pBullet->setID(tempID);
		bulletsMap[tempID] =  pBullet;
	}
}

void BulletManager::deleteBullet(int pID)
{
	if (hasBullet(pID))
	{
		bulletsMap[pID]->bulletRelease();
		bulletsMap.erase(pID);
	}
}

IBullet* BulletManager::getBullet(int pID)
{
	if (hasBullet(pID))
	{
		return bulletsMap.at(pID);
	}
	return NULL;
}

bool BulletManager::hasBullet(int pID)
{
	if (bulletsMap.find(pID) == bulletsMap.end())
	{
		return false;
	}
	return true;
}

void BulletManager::update()
{
	log("EnterTime");
	for (auto p : bulletsMap)
	{
		p.second->excute();
	}
}
