#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_
#include "Weapon.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class Shotgun :
	public Weapon
{
public:
	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	static Shotgun* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();


	virtual void update(float dt);

	//单次攻击,未实现
	virtual void attack(float dt);
};


inline void Shotgun::updateRotation()
{
	setFlipY(_direction.x <= 0);
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}

#endif
