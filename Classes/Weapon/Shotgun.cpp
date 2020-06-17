#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"Shotgun.h"

Shotgun::Shotgun()
{
}


Shotgun::~Shotgun()
{
}
Shotgun* Shotgun::createWithName(std::string weaponName)
{
	Shotgun* weapon = new(std::nothrow)Shotgun;
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool Shotgun::initWithName(std::string weaponName)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;

	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);

	return true;
}

void Shotgun::initWithValueMap(ValueMap valueMap)
{
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Shotgun::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

void Shotgun::attack(float dt) {
	auto bullet1 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	auto bullet2 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	auto bullet3 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	bullet1->setFlag(getFlag());
	bullet2->setFlag(getFlag());
	bullet3->setFlag(getFlag());

	//子弹模型
	auto bulletSize = bullet1->getContentSize();
	auto bulletBody1 = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody1->setDynamic(false);
	auto bulletBody2 = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody2->setDynamic(false);
	auto bulletBody3 = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody3->setDynamic(false);
	bullet1->setPhysicsBody(bulletBody1);
	bullet2->setPhysicsBody(bulletBody2);
	bullet3->setPhysicsBody(bulletBody3);

	//子弹位置和角度
	auto weaponSize = getContentSize();
	auto dir = getDirection();
	Vec2 angle20(0.9397, 0.342);
	auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto sinadd20 = sin * angle20.x + cos * angle20.y;
	auto cosadd20 = cos * angle20.x - sin * angle20.y;
	auto sinmin20 = sin * angle20.x - cos * angle20.y;
	auto cosmin20 = cos * angle20.x + sin * angle20.y;
	CCRotateTo* rt1 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	CCRotateTo* rt2 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle() + angle20.getAngle()));
	CCRotateTo* rt3 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle() - angle20.getAngle()));

	
	bullet1->runAction(rt1);
	bullet2->runAction(rt2);
	bullet3->runAction(rt3);
	auto weaponPosition = getPosition();

	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	runningLayer->addChild(bullet1, 6);
	runningLayer->addChild(bullet2, 6);
	runningLayer->addChild(bullet3, 6);

	bullet1->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.width / 2);
	bullet1->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
	bullet2->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.width / 2);
	bullet2->getPhysicsBody()->setVelocity(Vec2(100 * cosadd20, 100 * sinadd20));
	bullet3->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.width / 2);
	bullet3->getPhysicsBody()->setVelocity(Vec2(100 * cosmin20, 100 * sinmin20));
}
