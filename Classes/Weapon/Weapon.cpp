#include "Weapon.h"
#include"Weapon/Shotgun.h"
#include"Weapon/SingleShotgun.h"
#include"Weapon/MeleeWeapon.h"
#include"Actor/Hero.h"
#include"Actor/MovingActor.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"
#include"Actor/Monster.h"

Weapon* Weapon::createWithName(std::string weaponName)
{
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	auto weaponType = VALUE_AT(thisMap, "weaponType", String);
	Weapon* weapon = NULL;
	WEAPON_JUDGE(weaponType, Shotgun);
	WEAPON_JUDGE(weaponType, SingleShotgun);
	WEAPON_JUDGE(weaponType, MeleeWeapon);
	if (weapon && weapon->initWithName(weaponName, thisMap))
	{
		weapon->retain();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool Weapon::initWithName(std::string weaponName,ValueMap valueMap)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;
	MainScene::SharedScene()->getMapLayer()->addActorToVec(this);
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "WeaponDefaultData.plist");
	initData(VALUE_AT(defaultMap, "CommonData", ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));
	weaponOff();
	initWithValueMap(valueMap);
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
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}


//拿上武器,还要考虑设置位置的事情
void  Weapon::weaponOn(MovingActor* myHero)
{
	removeFromParent();
	myHero->addChild(this);
	auto Parent = dynamic_cast<Actor*> (getParent());
	setFlag(Parent->getFlag());
	myHero->setMainWeapon(this);
	_on = true;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->removeActorFromVec(this);
	if (dynamic_cast<Monster*>(getParent())) {
		setAnchorPoint(Vec2(0.5f, 0.5f));
		setPosition(myHero->getContentSize() / 2);
	}
	if (dynamic_cast<Hero*>(getParent()))
	    schedule(schedule_selector(Weapon::updateRotation));
	//换掩码
	bitMaskOn();
	
}

//换下武器，还要考虑设置位置的事情
void  Weapon::weaponOff()
{
	bitMaskOff();
	_on = false;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->addActorToVec(this);
	auto pos = map->convertToNodeSpace(convertToWorldSpace(getPosition()));
	removeFromParent();
	map->addChild(this);

	//关闭时间调度器
	unschedule(schedule_selector(Weapon::updateRotation));
	unschedule(schedule_selector(Weapon::attack));

	setPosition(pos);
	setDirection(Vec2(1, 0));
	updateRotation(0);
}


void Weapon::attack(float dt) {
	if (!Director::getInstance()->getRunningScene())
		return;
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	if (!runningScene)
		return;
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	Hero* myHero = runningScene->getHero();

	auto bullet = Sprite::createWithTexture(getBulletTexture());

	//子弹模型
	auto bulletSize = getContentSize();
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

	runningLayer->addChild(bullet, 6);
	
	bullet->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.height / 2);
	bullet->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
}

void Weapon::bitMaskOn()
{
	auto body = getPhysicsBody();
	if (body)
	{
		body->setCategoryBitmask(WEAPON_CATAGORY);
		body->setCollisionBitmask(WEAPON_COLLISION);
		int contact= WEAPON_CONTACT;
		if (_flag == FLAG_HERO)
			contact ^= HERO_CATAGORY;
		else if (_flag == FLAG_MONSTER)
			contact ^= MONSTER_CATAGORY;
		body->setContactTestBitmask(contact);
	}
}

void Weapon::bitMaskOff()
{
	auto body = getPhysicsBody();
	if (body)
	{
		body->setCategoryBitmask(PROP_CATAGORY);
		body->setCollisionBitmask(PROP_COLLISION);
		body->setContactTestBitmask(PROP_CONTACT);
	}
}

void Weapon::updateNohurt(float dt)
{
	setFlag(FLAG_NOHURT);
	auto Parent = static_cast<Actor*> (getParent());
	if (Parent->getName() == "Monster")
	{
		Parent = static_cast<Monster*> (Parent);
		Parent->schedule(schedule_selector(Monster::updateWeaponDirection));
	}
}

bool Weapon::onContactBegin(Actor *a2)
{
	if (_on)
		return weaponOnContact(a2);
	else
		return weaponOffContact(a2);
}

bool Weapon::onContactSeparate(Actor * a2)
{
	if (!_on)
		MainScene::SharedScene()->onTPressed= nullptr;
	return false;
}

bool Weapon::weaponOffContact(Actor *a2)
{
	if (a2->getName() == "Hero")
	{
		auto hero = MainScene::SharedScene()->getHero();
		hero->setWeaponToOn(this);
		MainScene::SharedScene()->onTPressed = CC_CALLBACK_0(Hero::changeWeapon, hero);
	}
	return false;
}

bool Weapon::weaponOnContact(Actor *a2)
{
	if (isAnotherFlag(a2) && (a2->getFlag() != FLAG_NOHURT))
	{
		getHurt(a2->getDamage());
	}
	return false;
}
