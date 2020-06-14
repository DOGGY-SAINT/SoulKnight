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
	//�����ʼ��
	static Box* createWithObject(ValueMap);

	//�����ʼ��
	bool initWithObject(ValueMap)override;

	//���ֶԵ���
	void randAllProp();

	void randProp(ValueMap);

	void randWeapon(ValueMap);

	bool onContactBegin(Actor*)override;

	bool onContactSeparate(Actor*)override;

	bool isOpen() { return _open; }

	void openBox();
};

