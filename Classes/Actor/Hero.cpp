#include"Bullet.h"
#include"Hero.h"
#include "Component\Constant.h"
#include"Weapon/Weapon.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"

//hero需要手动release
//密度 弹性 摩擦力
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
	retain();
	_on = true;
	_heroToOn = nullptr;
	auto file = FileUtils::getInstance();
	auto valueMap = file->getValueMapFromFile(PATH_DATA + "HeroData.plist");
	setAnchorPoint(Vec2::ZERO);

	initController();
	initData(VALUE_AT(valueMap, "CommonData", ValueMap));
	initState(VALUE_AT(valueMap, Name, ValueMap));
	initCollision(VALUE_AT(valueMap, "CollisionData", ValueMap));
	initWeapon(DEFAULT_WEAPON_NAME);
	initScheduler();
	return true;
}

Hero* Hero::createWithObject(ValueMap valueMap)
{
	Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->initWithObject(valueMap))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::initWithObject(ValueMap valueMap)
{
	if (!initWithName(VALUE_AT(valueMap, "HeroName", String)))
		return false;
	_on = false;
	setAnchorPoint(Vec2::ZERO);
	auto position = MapLayer::getObjectNodeSpace(valueMap);
	setPosition(position);
	heroOff();
	return true;
}



void Hero::initData(ValueMap valueMap)
{
	SET_DATA(valueMap, CanBeHurt, Bool);
	SET_DATA(valueMap, Damage, Int);
	SET_DATA(valueMap, LocalZOrder, Int);
	SET_DATA(valueMap, Flag, Int);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, V, Int);
	_weaponToOn = nullptr;
}

void Hero::initCollision(ValueMap valueMap)
{
	auto body = PhysicsBody::createBox(getContentSize(), defaultMaterial);
	auto b = VALUE_AT(valueMap, "Name", String);
	body->SET_DATA(valueMap, Name, String);
	auto b2 = VALUE_AT(valueMap, "CategoryBitmask", String);
	body->SET_DATA(valueMap, CategoryBitmask, Int);
	body->SET_DATA(valueMap, CollisionBitmask, Int);
	body->SET_DATA(valueMap, ContactTestBitmask, Int);
	body->SET_DATA(valueMap, Dynamic, Bool);
	body->SET_DATA(valueMap, VelocityLimit, Float);
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

bool Hero::onContactBegin(Actor *a2)
{
	if (_on)
		return heroOnContact(a2);
	else
		return heroOffContact(a2);
}

bool Hero::onContactSeparate(Actor *)
{
	if (!_on)
		MainScene::SharedScene()->onTPressed = nullptr;
	return false;
}

bool Hero::heroOnContact(Actor *a2)
{
	if (isAnotherFlag(a2) && a2->getFlag() != FLAG_NOHURT)
	{
		getHurt(a2->getDamage());
		return true;
	}
	return false;
}

bool Hero::heroOffContact(Actor *a2)
{
	if (a2->getName() == "Hero")
	{
		auto mainScene = MainScene::SharedScene();
		mainScene->getHero()->setHeroToOn(this);
		mainScene->onTPressed=CC_CALLBACK_0(MainScene::changeHero, mainScene);
	}
	return false;
}

void Hero::heroOn()
{
	_on = true;
	auto mainScene = MainScene::SharedScene();
	mainScene->setHero(this);
	mainScene->getMapLayer()->removeActorFromVec(this);
	mainScene->getMapLayer()->removeActorFromVec(_mainWeapon);
	initScheduler();

	auto body = getPhysicsBody();
	body->setCategoryBitmask(HERO_CATAGORY);
	body->setCollisionBitmask(HERO_COLLISION);
	body->setContactTestBitmask(HERO_CONTACT);
}

void Hero::heroOff()
{
	_on = false;
	auto mainScene = MainScene::SharedScene();
	removeScheduler();
	initController();
	if (mainScene->getHero() == this)
		mainScene->setHero(nullptr);
	mainScene->getMapLayer()->addActorToVec(this);
	mainScene->getMapLayer()->addActorToVec(_mainWeapon);

	auto body = getPhysicsBody();
	body->setVelocity(Vec2::ZERO);
	body->setCategoryBitmask(PROP_CATAGORY);
	body->setCollisionBitmask(PROP_COLLISION);
	body->setContactTestBitmask(PROP_CONTACT);
}

void Hero::initState(ValueMap valueMap)
{
	_HP = State(VALUE_AT(valueMap, "HP", ValueMap));
	_AC = State(VALUE_AT(valueMap, "AC", ValueMap));
	_power = State(VALUE_AT(valueMap, "Power", ValueMap));
}

void Hero::initController()
{
	_wPressed = false;
	_aPressed = false;
	_sPressed = false;
	_dPressed = false;
}


void Hero::initScheduler()
{
	schedule(schedule_selector(Hero::updateV));
	schedule(schedule_selector(Hero::updateHP), _HP.getRecoverGap());
	schedule(schedule_selector(Hero::updateAC), _AC.getRecoverGap());
	schedule(schedule_selector(Hero::updatePower), _power.getRecoverGap());
}

void Hero::removeScheduler()
{
	unschedule(schedule_selector(Hero::updateV));
	unschedule(schedule_selector(Hero::updateHP));
	unschedule(schedule_selector(Hero::updateAC));
	unschedule(schedule_selector(Hero::updatePower));
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

void Hero::updateV(float dt)
{
	auto v = _v * Vec2(_dPressed - _aPressed, _wPressed - _sPressed);
	getPhysicsBody()->setVelocity(v);
}

void Hero::changeWeapon()
{
	if (_weaponToOn)
	{
		_mainWeapon->weaponOff();
		_weaponToOn->weaponOn(this);
	}
}

