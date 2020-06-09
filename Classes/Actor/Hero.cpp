#include"Bullet.h"
#include"Hero.h"
#include "Component\Constant.h"
#include"Weapon/Weapon.h"

//ÃÜ¶È µ¯ÐÔ Ä¦²ÁÁ¦
const PhysicsMaterial Hero::defaultMaterial = PhysicsMaterial(0.0f, 0.0f, 0.0f);

Hero* Hero::createWithName(std::string Name)
{
	Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->initWithName(Name))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::initWithName(std::string Name)
{
	if (!Sprite::initWithFile(PATH_PICTURE_HERO + Name + ".png"))
		return false;
	auto file = FileUtils::getInstance();
	auto valueMap = file->getValueMapFromFile(PATH_DATA + "HeroData.plist");

	initController();
	initData(VALUE_AT(valueMap, "CommonData", ValueMap));
	initState(VALUE_AT(valueMap, Name, ValueMap));
	initCollision(VALUE_AT(valueMap, "CollisionData", ValueMap));
	_weapon1 = Weapon::createWithName(DEFAULT_WEAPON_NAME);
	_weapon1->setPosition(Vec2::ZERO);
	addChild(_weapon1);
	return true;
}

bool Hero::initWithHero(Hero* hero)
{
	return false;
}

Hero* Hero::createWithHero(Hero* hero)
{
	/*Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->initWithHero(hero))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;*/
	return nullptr;
}

void Hero::initData(ValueMap valueMap)
{
	SET_DATA(valueMap, CanBeHurt, Bool);
	SET_DATA(valueMap, Damage, Int);
	SET_DATA(valueMap, LocalZOrder, Int);
	SET_DATA(valueMap, Flag, Int);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, V, Int);
}

void Hero::initCollision(ValueMap valueMap)
{
	auto body = PhysicsBody::createBox(getContentSize(), defaultMaterial);
	auto b= VALUE_AT(valueMap, "Name", String);
	body->SET_DATA(valueMap, Name, String);
	auto b2 = VALUE_AT(valueMap, "CategoryBitmask", String);
	body->SET_DATA(valueMap, CategoryBitmask, Int);
	body->SET_DATA(valueMap, CollisionBitmask, Int);
	body->SET_DATA(valueMap, ContactTestBitmask, Int);
	/*auto s = VALUE_AT(valueMap, "Dynamic", Bool);*/
	body->SET_DATA(valueMap, Dynamic, Bool);
	/*auto s2 = VALUE_AT(valueMap, "RotationEnable", Bool);*/
	body->SET_DATA(valueMap, RotationEnable, Bool);
	addComponent(body);
}

void Hero::getHurt(INT32 dmg)
{
	INT32 correct = 0;
	if (_AC.getState() - dmg < 0)
		correct = dmg - _AC.getState();
	_AC.setStateBy(-dmg);
	_HP.setStateBy(-correct);
	if (isDead())
		afterDead();
}

void Hero::initState(ValueMap valueMap)
{
	_HP = State(VALUE_AT(valueMap,"HP",ValueMap));
	_AC = State(VALUE_AT(valueMap, "AC", ValueMap));
	_power = State(VALUE_AT(valueMap, "Power", ValueMap));

	schedule(schedule_selector(Hero::updateHP), _HP.getRecoverGap());
	schedule(schedule_selector(Hero::updateAC), _AC.getRecoverGap());
	schedule(schedule_selector(Hero::updatePower), _power.getRecoverGap());
}

void Hero::initController()
{
	_wPressed = false;
	_aPressed = false;
	_sPressed = false;
	_dPressed = false;
}


void Hero::updateHP(float dt)
{
	_HP.updateRecover(dt);
}


void Hero::updateAC(float dt)
{
	_AC.updateRecover(dt);
}

void Hero::updatePower(float dt)
{
	_power.updateRecover(dt);
}