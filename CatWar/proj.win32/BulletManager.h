#pragma once

#include "IBullet.h"
#include "FishboneBullet.h"
#include <unordered_map>
//#include "GameScene.h"

using namespace std;

class BulletManager
{
public:
	BulletManager() = default;
	~BulletManager() = default;

	static void addBullet(int type);
	static void deleteBullet(int pID);
	static IBullet* getBullet(int pID);
	static bool hasBullet(int pID);
	static void update();
private:
	static unordered_map<int, IBullet*> bulletsMap;
	static int validID;
};

