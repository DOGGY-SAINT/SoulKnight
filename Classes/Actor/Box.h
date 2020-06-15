#pragma once

#include"cocos2d.h"
#include"Actor/Actor.h"

class Box 
	:public Actor
{
	CC_SYNTHESIZE(Actor*, _prop, Prop);
public:
	//对象初始化
	static Box* createWithObject(ValueMap);

	//对象初始化
	virtual bool initWithObject(ValueMap);

	void initProp(ValueMap);

};

