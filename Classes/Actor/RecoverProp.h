#pragma once
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

class RecoverProp
	:public Actor
{
	enum {HP,Power};
	CC_SYNTHESIZE(INT32, _type, Type);
	CC_SYNTHESIZE(INT32, _recoverNum, RecoverNum);

	bool onContactBegin(Actor*)override;

	void initData(ValueMap)override;

};

