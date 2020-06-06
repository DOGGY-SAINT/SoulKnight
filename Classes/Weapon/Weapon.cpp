#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"

Weapon* Weapon::createWithName(std::string weaponName)
{
	Weapon* weapon = new(std::nothrow)Weapon;
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool Weapon::initWithName(std::string weaponName)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "Weapon.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);

	return true;
}

void Weapon::initWithValueMap(ValueMap valueMap)
{
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Weapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + getName() + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

//拿上武器,还要考虑设置位置的事情
void  Weapon::weaponOn()
{
	schedule(schedule_selector(Weapon::updateRotation));
}

//换下武器，还要考虑设置位置的事情
void  Weapon::weaponOff()
{
	setDirection(Vec2(1, 0));
	updateRotation(0);
	unschedule(schedule_selector(Weapon::updateRotation));
	unschedule(schedule_selector(Weapon::attack));
}