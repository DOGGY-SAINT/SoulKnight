#ifndef _WEAPON_H_
#define _WEAPON_H_
#include"Actor/Bullet.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
#include"Actor/Hero.h"
#include"Actor/MovingActor.h"
USING_NS_CC;

//Weapon可以考虑储存Bullet名字或者怎么样
class Weapon :
	public Actor
{

	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletData, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
	CC_SYNTHESIZE(bool, _on, IsOn);
	CC_SYNTHESIZE(int, _powerCost, PowerCost);
protected:
	Vec2 _direction;
public:
	bool onContactBegin(Actor* a2)override;

	bool weaponOffContact(Actor*);

	bool weaponOnContact(Actor*);


	Vec2 getDirection() { return _direction; }

	void setDirection(Vec2 dir) { _direction = dir; updateRotation(); }

	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName, ValueMap valueMap);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//拿上武器
	virtual void weaponOn(MovingActor* myHero);

	//换下武器
	virtual void weaponOff();

	//单次攻击
	virtual void attack(float dt);

	void bitMaskOn();

	void bitMaskOff();

	void updateNohurt(float dt);
};

//设定了delay
inline void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}




#endif