#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"MeleeWeapon.h"
#include"SimpleAudioEngine.h"
#include"iostream"

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
	//武器模型
	auto weaponSize = getContentSize();

	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);

	return true;
}

void MeleeWeapon::initWithValueMap(ValueMap valueMap)
{
	setAnchorPoint(Vec2(0.1, 0.5));

	SET_DATA(valueMap, PowerCost, Int);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	this->setScale(VALUE_AT(valueMap, "Scale", Float));
	initBulletData(valueMap);
}


void MeleeWeapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	_damage = VALUE_AT(_bulletData,"Damage",Int);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

void MeleeWeapon::update(float dt) {
	updateRotation();
}

void  Weapon::weaponOn(MovingActor* myHero)
{
	removeFromParent();
	myHero->addChild(this);
	auto Parent = dynamic_cast<Actor*> (getParent());
	updateNohurt(0);
	myHero->setMainWeapon(this);
	_on = true;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->removeActorFromVec(this);

	setPosition(myHero->getContentSize().width / 2 - 10, myHero->getContentSize().height / 2 - 10);
	//换掩码
	bitMaskOn();

}



void MeleeWeapon::attack(float dt) {
	//获取hero信息
	if (dynamic_cast<Hero*>(getParent())) {
		auto Parent = dynamic_cast<Hero*> (getParent());
			//判断能量
		State* power = Parent->getPower();
		if (power->getState() < _powerCost)
			return;
		power->setStateTo(power->getState() - _powerCost);
	}

	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	Hero* myHero = runningScene->getHero();
	setFlag(myHero->getFlag());
	Vec2 angle60(1, 1.732);
	CCRotateBy* rt0 = CCRotateBy::create(0, -CC_RADIANS_TO_DEGREES(angle60.getAngle()));
	CCRotateBy* rt1 = CCRotateBy::create(_gapTime*0.6, CC_RADIANS_TO_DEGREES(2 * angle60.getAngle()));
	CCRotateBy* rt2 = CCRotateBy::create(_gapTime*0.3, -CC_RADIANS_TO_DEGREES(2 * angle60.getAngle()));
	runAction(CCSequence::create(rt0,rt1,rt2,NULL));
	updateRotation();
	scheduleOnce(schedule_selector(MeleeWeapon::updateNohurt),_gapTime*0.9);
	//音效
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	String s = "music/" + getName() + ".mp3";
	if (audio->isBackgroundMusicPlaying() == 1)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s.getCString());
}
