#pragma once
#include"Actor.h"
#include"cocos2d.h"
#include<vector>
USING_NS_CC;

class Weapon;

class MovingActor
	:public Actor
{
	CC_SYNTHESIZE(Weapon*, _mainWeapon, MainWeapon);
	//速度最大值
	CC_SYNTHESIZE(INT32, _velocityLim, VelocityLim);
	//一般的速度大小
	CC_SYNTHESIZE(INT32, _v, V);

public:
	void initCollision(ValueMap)override;

	virtual void setAttackOn();

	virtual void setAttackOff();

	virtual void initWeapon(std::string weaponName);

	
};

