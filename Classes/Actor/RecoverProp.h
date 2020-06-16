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

	static RecoverProp* createWithName(std::string);

	bool initWithName(std::string);

	void initOther(ValueMap);

	bool onContactBegin(Actor*)override;

	void recover();

};

