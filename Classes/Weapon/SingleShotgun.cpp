#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"SingleShotgun.h"

SingleShotgun::SingleShotgun()
{
}


SingleShotgun::~SingleShotgun()
{
}
SingleShotgun* SingleShotgun::createWithName(std::string weaponName)
{
	SingleShotgun* weapon = new(std::nothrow)SingleShotgun;
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool SingleShotgun::initWithName(std::string weaponName)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;

	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);

	return true;
}

void SingleShotgun::initWithValueMap(ValueMap valueMap)
{
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void SingleShotgun::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

void SingleShotgun::attack(float dt) {
	auto bullet = Sprite::createWithTexture(getBulletTexture());

	//子弹模型
	auto bulletSize = bullet->getContentSize();
	auto bulletBody = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody->setDynamic(false);
	bullet->setPhysicsBody(bulletBody);

	//子弹位置和角度
	auto weaponSize = getContentSize();
	auto dir = getDirection();
	auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	bullet->runAction(rt);
	auto weaponPosition = getPosition();

	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMyMapLayer());
	runningLayer->addChild(bullet, 6);

	//float x = weaponPosition.x - sin * weaponSize.height / 2 + cos * weaponSize.width / 2;
	//float y = weaponPosition.y + cos * weaponSize.height / 2 + sin * weaponSize.width / 2;
	float x = weaponPosition.x - sin * 10 + cos * 29;
	float y = weaponPosition.y + cos * 10 + sin * 29;
	bullet->setPosition(Vec2(x, y));
	bullet->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
}
