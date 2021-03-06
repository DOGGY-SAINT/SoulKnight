#include "Monster.h"
#include"Component/Constant.h"
#include"Scene/MapLayer.h"
#include"Scene/MainScene.h"
#include"Actor/Hero.h"
#include"Weapon/Weapon.h"

Monster * Monster::createWithObject(ValueMap valueMap)
{
	Monster* monster = new(std::nothrow)Monster;
	if (monster && monster->initWithObject(valueMap))
	{
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

bool Monster::initWithObject(ValueMap valueMap)
{
	if (!Sprite::initWithFile(VALUE_AT(valueMap, "TexturePath", String)))
		return false;
	setAnchorPoint(Vec2::ZERO);
	auto position = MapLayer::getObjectNodeSpace(valueMap);
	setPosition(position);
	initData(valueMap);
	initCollision(valueMap);
	initWeapon(VALUE_AT(valueMap,"WeaponName",String));
	initScheduler();
	return true;
}

void Monster::initScheduler()
{
	schedule(schedule_selector(Monster::updateVelocity),0.2f);
	schedule(schedule_selector(Monster::updateWeaponDirection));
	setAttackOn();
}

void Monster::updateVelocity(float dt)
{
	auto dir = MainScene::SharedScene()->getHero()->getPosition() - getPosition();
	auto v0 = dir / dir.length()*_v;
	auto rand = Vec2(this->rand(),this->rand());
	auto body = getPhysicsBody();
	body->setVelocity(v0+rand);
}

void Monster::updateWeaponDirection(float dt)
{
	auto dir = MainScene::SharedScene()->getHero()->getPosition() - getPosition();
	_mainWeapon->setDirection(dir);
}

inline float Monster::rand()
{
	auto num = std::rand() % (200*_v) - 100*_v;
	float f = num / 100.0f;
	return f;
}

void Monster::setAttackOn()
{
	if (_mainWeapon)
	{
		float gapTime = _mainWeapon->getGapTime();
		_mainWeapon->schedule(schedule_selector(Weapon::attack), gapTime*2, CC_REPEAT_FOREVER, gapTime / 2);
	}
}
