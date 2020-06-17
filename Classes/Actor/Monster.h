#ifndef _MONSTER_H_
#define _MONSTER_H_

#include"cocos2d.h"
#include"MovingActor.h"
USING_NS_CC;
class Monster 
	:public MovingActor
{
public:
	static Monster* createWithObject(ValueMap);

	bool initWithObject(ValueMap)override;

	void initScheduler();

	void updateVelocity(float dt);

	void updateWeaponDirection(float dt);

	float rand();
};


#endif 