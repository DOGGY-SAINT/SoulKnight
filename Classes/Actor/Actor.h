#ifndef _ACTOR_H_
#define _ACTOR_H_
//All Sprite with PhysicBody is Actor
#include "cocos2d.h"
#include"Component/State.h"

USING_NS_CC;

class Actor
	:public Sprite
{
	CC_SYNTHESIZE(INT32, _damage, Damage);
	CC_SYNTHESIZE(INT32, _flag, Flag);
protected:
	bool _canBeHurt = false;
	State _HP;
public:
	//默认函数,对自己做的事情
	inline virtual bool onContactBegin(Actor* a2);

	inline bool isAnotherFlag(Actor* a2);

	//默认材料
	static const PhysicsMaterial defaultMaterial;

	//set&get
	inline void setCanBeHurt(bool num);
	inline bool getCanBeHurt();

	//create
	static Actor* createWithSprite(Sprite*, ValueMap);

	//精灵初始化，复制了texture，rect，position
	virtual bool initWithSprite(Sprite*, ValueMap);

	//对象初始化
	static Actor* createWithObject(ValueMap);
	
	//对象初始化
	virtual bool initWithObject(ValueMap);

	//数据初始化
	virtual void initData(ValueMap);

	//Body初始化
	virtual void initCollision(ValueMap);

	//掉血
	inline virtual void getHurt(INT32 dmg);

	inline bool isDead();

	//死亡回调
	inline virtual void afterDead();
};





#endif 