#pragma once

#include"cocos2d.h"
#include"Actor/Actor.h"

class Box 
	:public Actor
{
	CC_SYNTHESIZE(Actor*, _prop, Prop);
private:
	bool _open=false;
public:
	//对象初始化
	static Box* createWithObject(ValueMap);

	//对象初始化
	bool initWithObject(ValueMap)override;

	//名字对道具
	void randAllProp();

	void randProp(ValueMap);

	void randWeapon(ValueMap);

	bool onContactBegin(Actor*)override;

	bool onContactSeparate(Actor*)override;

	bool isOpen() { return _open; }

	void openBox();
};

