#ifndef _WEAPON_H_
#define _WEAPON_H_
#include"Actor/Bullet.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

//Weapon可以考虑储存Bullet名字或者怎么样
class Weapon :
	public Actor
{
	
	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletDate, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
	CC_SYNTHESIZE(Vec2, _direction, Direction);

    public:
	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	virtual bool initWithName(std::string weaponName)=0;

	virtual void initWithValueMap(ValueMap)=0;

	virtual void initBulletData(ValueMap)=0;

	virtual inline void updateRotation();

	//拿上武器
	virtual void weaponOn();

	//换下武器
	virtual void weaponOff();

	//单次攻击
	virtual void attack(float dt)=0;
};

//设定了delay
inline void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}




#endif