#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"SingleShotgun.h"
#include"SimpleAudioEngine.h"

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
	SET_DATA(valueMap, PowerCost, Int);
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

	auto bullet = Bullet::createByTexture(getBulletTexture(),getBulletData());
	bullet->setFlag(getFlag());

	//子弹模型
	auto bulletSize = bullet->getContentSize();

	//子弹位置和角度
	auto weaponSize = getContentSize();
	auto dir = getDirection();
	auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto pending = _direction.x / abs(_direction.x);
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	bullet->runAction(rt);

	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	if (!runningScene)
		return;
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	auto myHero = runningScene->getHero();

	runningLayer->addChild(bullet, 6);

	auto heroPosition = getParent()->getPosition();
	auto weaponPosition = getPosition();
	auto hx = heroPosition.x, hy = heroPosition.y;
	auto wx = weaponPosition.x, wy = weaponPosition.y;

	//float x = weaponPosition.x - sin * weaponSize.height / 2 + cos * weaponSize.width / 2;
	//float y = weaponPosition.y + cos * weaponSize.height / 2 + sin * weaponSize.width / 2;
	float x = hx + wx - pending * sin * height + cos * width;
	float y = hy + wy + pending * cos * height + sin * width;
	bullet->setPosition(Vec2(x, y));
	bullet->getPhysicsBody()->setVelocity(Vec2(300 * cos, 300 * sin));
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying() == 1)
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/SingleShotgun.mp3");
}
