#ifndef _HERO_H_
#define _HERO_H_

#include"cocos2d.h"
#include"Actor.h"
USING_NS_CC;
class Weapon;

class Hero 
	:public Actor
{
protected:
	//护甲
	State _AC;
	//蓝量
	State _power;
	CC_SYNTHESIZE(Weapon*, _weapon1, Weapon1);
	CC_SYNTHESIZE(Vec2, _velocityTo, VelocityTo);
	CC_SYNTHESIZE(INT32, _v, V);
public:

	static Hero* createWithName(std::string);

	virtual bool initWithName(std::string);

	void initData(ValueMap)override;

	void initCollision(ValueMap)override;

	//初始化HP，AC，Power，开启自动恢复
	void initState(ValueMap);

	void initWeapon(ValueMap);

	void changeWeapon(Weapon*);

	virtual void getHurt(INT32 dmg)override;

	inline void moveChange(Vec2 vec);

};

//初始化，开启恢复


inline void Hero::moveChange(Vec2 vec)
{
	_velocityTo += vec * _v;
}

#endif 