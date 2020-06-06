#include"Bullet.h"
#include"Hero.h"
#include "Component\Constant.h"
#include"Weapon/Weapon.h"

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

	initData(VALUE_AT(valueMap, "CommonData", ValueMap));
	initState(VALUE_AT(valueMap, Name, ValueMap));
	initCollision(VALUE_AT(valueMap, "CollisionData", ValueMap));

	_weapon1 = Weapon::createWithName(DEFAULT_WEAPON_NAME);
	_weapon1->setPosition(Vec2::ZERO);
	addChild(_weapon1);
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
	body->SET_DATA(valueMap, Name, String);
	body->SET_DATA(valueMap, CategoryBitmask, Int);
	body->SET_DATA(valueMap, CollisionBitmask, Int);
	body->SET_DATA(valueMap, ContactTestBitmask, Int);
	body->SET_DATA(valueMap, Dynamic, Bool);
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
	/*_HP = State(VALUE_AT(valueMap, "HP", ValueMap));
	if (_HP.getRecoverGap() != 0)
		schedule(CC_CALLBACK_1(State::Recover), _HP.getRecoverGap());
	_AC = State(VALUE_AT(valueMap, "AC", ValueMap));
	if (_AC.getRecoverGap() != 0)
		schedule(schedule_selector(State::Recover), _AC.getRecoverGap());
	_power = State(VALUE_AT(valueMap, "Power", ValueMap));
	if (_power.getRecoverGap() != 0)
		schedule(schedule_selector(_power.Recover), _power.getRecoverGap());*/
}