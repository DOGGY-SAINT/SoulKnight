#ifndef _SINGLESHOTGUN_H_
#define _SINGLESHOTGUN_H_
#include "Weapon.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class SingleShotgun :
	public Weapon
{
public:
	SingleShotgun();
	~SingleShotgun();
	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	static SingleShotgun* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//拿上武器,未完成
	//virtual void weaponOn();

	//换下武器，未完成
	//virtual void weaponOff();


	//单次攻击
	virtual void attack(float dt);
};


inline void SingleShotgun::updateRotation()
{
	setFlipY(_direction.x <= 0);
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}
#endif
