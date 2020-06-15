#ifndef _MONSTER_H_
#define _MONSTER_H_

#include"cocos2d.h"
#include"MovingActor.h"
USING_NS_CC;
class Monster 
	:public MovingActor
{
	static Monster* createWithObject(ValueMap);

	bool initWithObject(ValueMap)override;

	void initData(ValueMap);

	void initCollision(ValueMap);

	void initWeapon(std::string name);

	void initSchedule();

	void updateVelocity(float dt);

	void updateWeaponDirection(float dt);
};


#endif 