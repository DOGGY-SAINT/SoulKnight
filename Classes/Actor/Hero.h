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
	//����
	State _AC;
	//����
	State _power;
	CC_SYNTHESIZE(Weapon*, _weapon1, Weapon1);
	CC_SYNTHESIZE(Vec2, _velocityTo, VelocityTo);
	CC_SYNTHESIZE(INT32, _v, V);
public:

	static Hero* createWithName(std::string);

	virtual bool initWithName(std::string);

	void initData(ValueMap)override;

	void initCollision(ValueMap)override;

	//��ʼ��HP��AC��Power�������Զ��ָ�
	void initState(ValueMap);

	void initWeapon(ValueMap);

	void changeWeapon(Weapon*);

	virtual void getHurt(INT32 dmg)override;

	inline void moveChange(Vec2 vec);

};

//��ʼ���������ָ�


inline void Hero::moveChange(Vec2 vec)
{
	_velocityTo += vec * _v;
}

#endif 