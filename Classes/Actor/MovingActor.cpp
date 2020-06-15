#include "MovingActor.h"
#include"Weapon/Weapon.h"

void MovingActor::setAttackOn()
{
	if (_mainWeapon)
	{
		float gapTime = _mainWeapon->getGapTime();
		_mainWeapon->schedule(schedule_selector(Weapon::attack, _mainWeapon), gapTime, CC_REPEAT_FOREVER, gapTime / 2);
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
