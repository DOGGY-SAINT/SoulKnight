#pragma once

#include"cocos2d.h"
#include"Actor/Actor.h"

class Box 
	:public Actor
{
	CC_SYNTHESIZE(Actor*, _prop, Prop);
public:
	//�����ʼ��
	static Box* createWithObject(ValueMap);

	//�����ʼ��
	virtual bool initWithObject(ValueMap);

	void initProp(ValueMap);

};

