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
	CC_SYNTHESIZE(bool, _wPressed, WPressed);
	CC_SYNTHESIZE(bool, _aPressed, APressed);
	CC_SYNTHESIZE(bool, _sPressed, SPressed);
	CC_SYNTHESIZE(bool, _dPressed, DPressed);
	CC_SYNTHESIZE(INT32, _v, V);
public:
	static const PhysicsMaterial defaultMaterial;

	static Hero* createWithName(std::string);

	virtual bool initWithHero(Hero*);

	static Hero* createWithHero(Hero*);

	virtual bool initWithName(std::string);

	void initData(ValueMap)override;

	void initCollision(ValueMap)override;

	//初始化HP，AC，Power，开启自动恢复
	void initState(ValueMap);

	void initController();


	inline void controlVelocity();

	void updateHP(float dt);

	void updateAC(float dt);

	void updatePower(float dt);

	/*void initWeapon(ValueMap);

	void changeWeapon(Weapon*);*/

	void getHurt(INT32 dmg)override;

	

};

//初始化，开启恢复


inline void Hero::controlVelocity()
{
	auto v = _v * Vec2(_dPressed - _aPressed, _wPressed - _sPressed);
	getPhysicsBody()->setVelocity(v);
}

#endif 