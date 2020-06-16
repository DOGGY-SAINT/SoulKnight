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
	Shotgun();
	~Shotgun();
	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	static Shotgun* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//拿上武器,未完成
	//virtual void weaponOn();

	//换下武器，未完成
	//virtual void weaponOff();

	//按下鼠标左键
	inline void onLeftPressed();

	//松开鼠标左键
	inline void onLeftReleased();

	//单次攻击,未实现
	virtual void attack(float dt);
};

inline void Shotgun::onLeftPressed()
{
	schedule(schedule_selector(Shotgun::attack), _gapTime, CC_REPEAT_FOREVER, _gapTime);
}

inline void Shotgun::onLeftReleased()
{
	unschedule(schedule_selector(Shotgun::attack));
}

inline void Shotgun::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}

#endif
