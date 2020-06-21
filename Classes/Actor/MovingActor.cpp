#include "MovingActor.h"
#include"Weapon/Weapon.h"
#include"Component/Constant.h"

void MovingActor::initCollision(ValueMap valueMap)
{
	if (VALUE_AT(valueMap, "Collision", Bool))
	{
		SET_DATA(valueMap, V, Int);
		SET_DATA(valueMap, VelocityLim, Float);
		auto body = PhysicsBody::createBox(getContentSize(), defaultMaterial);
		body->SET_DATA(valueMap, Name, String);
		body->SET_DATA(valueMap, CategoryBitmask, Int);
		body->SET_DATA(valueMap, CollisionBitmask, Int);
		body->SET_DATA(valueMap, ContactTestBitmask, Int);
		body->SET_DATA(valueMap, Dynamic, Bool);
		body->SET_DATA(valueMap, RotationEnable, Bool);
		body->setVelocityLimit(_velocityLim);
		setPhysicsBody(body);
	}
}

void MovingActor::setAttackOn()
{
	if (_mainWeapon)
	{
		float gapTime = _mainWeapon->getGapTime();
		_mainWeapon->schedule(schedule_selector(Weapon::attack), gapTime, CC_REPEAT_FOREVER, gapTime / 5);
	}
}

void MovingActor::setAttackOff()
{
	if (_mainWeapon)
		_mainWeapon->unschedule(schedule_selector(Weapon::attack, _mainWeapon));
}

void MovingActor::initWeapon(std::string weaponName)
{
	auto weapon=Weapon::createWithName(weaponName);
	weapon->weaponOn(this);
}

