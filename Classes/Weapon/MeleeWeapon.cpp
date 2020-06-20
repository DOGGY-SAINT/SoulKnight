#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"MeleeWeapon.h"
#include"SimpleAudioEngine.h"

MeleeWeapon::MeleeWeapon()
{
}


MeleeWeapon::~MeleeWeapon()
{
}

MeleeWeapon* MeleeWeapon::createWithName(std::string weaponName)
{
	MeleeWeapon* weapon = new(std::nothrow)MeleeWeapon;
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool MeleeWeapon::initWithName(std::string weaponName)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);

	return true;
}

void MeleeWeapon::initWithValueMap(ValueMap valueMap)
{
	setAnchorPoint(Vec2(0.1, 0.5));
	_on = false;
	this->retain();
	auto map = MainScene::SharedScene()->getMapLayer();
	map->addActorToVec(this);									//添加到release列表
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "WeaponDefaultData.plist");
	initData(VALUE_AT(defaultMap, "CommonData", ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));

	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	setScale(VALUE_AT(valueMap, "Scale", Float));
	
	initBulletData(valueMap);
}


void MeleeWeapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

void MeleeWeapon::update(float dt) {
	updateRotation();
}


void MeleeWeapon::attack(float dt) {
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	Hero* myHero = runningScene->getHero();
	Vec2 angle60(1, 1.732);
	CCRotateBy* rt0 = CCRotateBy::create(0, -CC_RADIANS_TO_DEGREES(angle60.getAngle()));
	CCRotateBy* rt1 = CCRotateBy::create(_gapTime*0.6, CC_RADIANS_TO_DEGREES(2 * angle60.getAngle()));
	CCRotateBy* rt2 = CCRotateBy::create(_gapTime*0.3, -CC_RADIANS_TO_DEGREES(2 * angle60.getAngle()));
	runAction(CCSequence::create(rt0, rt1, rt2, NULL));
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying() == 1)
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("MeleeWeapon.mp3");
	updateRotation();
}
