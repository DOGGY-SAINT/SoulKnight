#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"Shotgun.h"
#include"SimpleAudioEngine.h"


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
	SET_DATA(valueMap, PowerCost, Int);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Shotgun::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(Director::sharedDirector()->getTextureCache()->addImage(bulletPath));
}

void Shotgun::update(float dt) {
	updateRotation();
}


void Shotgun::attack(float dt) {
	//获取hero信息
	if (dynamic_cast<Hero*>(getParent())) {
		auto Parent = dynamic_cast<Hero*> (getParent());
		//判断能量
		State* power = Parent->getPower();
		if (power->getState() < _powerCost)
			return;
		power->setStateTo(power->getState() - _powerCost);
	}

	if (!Director::getInstance()->getRunningScene())
		return;
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[getName()].asValueMap();
	auto width = VALUE_AT(thisMap, "SizeX", Int);
	auto height = VALUE_AT(thisMap, "SizeY", Int);

	auto bullet1 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	auto bullet2 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	auto bullet3 = Bullet::createByTexture(getBulletTexture(), getBulletData());
	bullet1->setFlag(getFlag());
	bullet2->setFlag(getFlag());
	bullet3->setFlag(getFlag());
	auto flag = bullet1->getFlag();

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
	auto pending = _direction.x / abs(_direction.x);
	CCRotateTo* rt1 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	CCRotateTo* rt2 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle() + angle20.getAngle()));
	CCRotateTo* rt3 = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle() - angle20.getAngle()));

	bullet1->runAction(rt1);
	bullet2->runAction(rt2);
	bullet3->runAction(rt3);

	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	if (!runningScene)
		return;
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	auto myHero = runningScene->getHero();

	runningLayer->addChild(bullet1, 6);
	runningLayer->addChild(bullet2, 6);
	runningLayer->addChild(bullet3, 6);

	auto parentPosition = getParent()->getPosition();
	auto weaponPosition = getPosition();
	auto hx = parentPosition.x, hy = parentPosition.y;
	auto wx = weaponPosition.x, wy = weaponPosition.y;

	float x = hx + wx - pending * sin * 5 / 2 + cos * 70 / 2;
	float y = hy + wy + pending * cos * 5 / 2 + sin * 70 / 2;

	bullet1->setPosition(x, y);
	bullet1->getPhysicsBody()->setVelocity(Vec2(200 * cos, 200 * sin));
	bullet2->setPosition(x, y);
	bullet2->getPhysicsBody()->setVelocity(Vec2(200 * cosadd20, 200 * sinadd20));
	bullet3->setPosition(x, y);
	bullet3->getPhysicsBody()->setVelocity(Vec2(200 * cosmin20, 200 * sinmin20));
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying() == 1)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/Shotgun.mp3");
}
