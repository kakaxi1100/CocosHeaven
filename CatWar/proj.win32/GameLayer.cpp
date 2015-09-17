#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bgLayer = BackgroudLayer::create();
	addChild(bgLayer);

	cat = Cat::create();
	//cat->setPosition(200, 100);
	addChild(cat);

	for (size_t i = 0; i < 3; i++)
	{

		Dog* dog = Dog::create();
		dog->setID(GameData::getAvailableID());
		dogs.insert(dog->getID(), dog);
		addChild(dog);
	}

	this->scheduleUpdate();

	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameLayer::testMsg), "test", NULL);


	/*draw = DrawNode::create();
	addChild(draw);*/
	return true;
}


void GameLayer::update(float delta)
{
	bgLayer->execute();

	cat->execute();
	for (auto &p : dogs)
	{
		cat->hitDog(p.second);
		p.second->execute();
		p.second->hitCat(cat);
	}

	/*dog->execute();
	dog->hitCat(cat);*/

	/*draw->clear();
	Vec2 point1[4];
	point1[0] = Point(cat->temp1.getMinX(), cat->temp1.getMaxY());
	point1[1] = Point(cat->temp1.getMaxX(), cat->temp1.getMaxY());
	point1[2] = Point(cat->temp1.getMaxX(), cat->temp1.getMinY());
	point1[3] = Point(cat->temp1.getMinX(), cat->temp1.getMinY());
	draw->drawPolygon(point1, 4, Color4F(0, 1, 0, 0), 1, Color4F(0, 1, 0, 1));

	Vec2 point2[4];
	point2[0] = Point(cat->temp2.getMinX(), cat->temp2.getMaxY());
	point2[1] = Point(cat->temp2.getMaxX(), cat->temp2.getMaxY());
	point2[2] = Point(cat->temp2.getMaxX(), cat->temp2.getMinY());
	point2[3] = Point(cat->temp2.getMinX(), cat->temp2.getMinY());
	draw->drawPolygon(point2, 4, Color4F(0, 1, 0, 0), 1, Color4F(0, 1, 0, 1));*/
}

void GameLayer::testMsg(Ref* pData)
{
	log("Recive!!!");
}
