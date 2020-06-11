#include "MovingActor.h"
#include"Weapon/Weapon.h"

void MovingActor::setAttackOn()
{
	if (_mainWeapon)
		_mainWeapon->schedule(schedule_selector(Weapon::attack,_mainWeapon));
}

void MovingActor::setAttackOff()
{
	if(_mainWeapon)
		_mainWeapon->unschedule(schedule_selector(Weapon::attack, _mainWeapon));
}
