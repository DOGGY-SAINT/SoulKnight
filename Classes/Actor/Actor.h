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
	//Ĭ�Ϻ���,���Լ���������
	inline virtual bool onContactBegin(Actor* a2);

	inline bool isAnotherFlag(Actor* a2);

	//Ĭ�ϲ���
	static const PhysicsMaterial defaultMaterial;

	//set&get
	inline void setCanBeHurt(bool num);
	inline bool getCanBeHurt();

	//create
	static Actor* createWithSprite(Sprite*, ValueMap);

	//�����ʼ����������texture��rect��position
	virtual bool initWithSprite(Sprite*, ValueMap);

	//�����ʼ��
	static Actor* createWithObject(ValueMap);
	
	//�����ʼ��
	virtual bool initWithObject(ValueMap);

	//���ݳ�ʼ��
	virtual void initData(ValueMap);

	//Body��ʼ��
	virtual void initCollision(ValueMap);

	//��Ѫ
	inline virtual void getHurt(INT32 dmg);

	inline bool isDead();

	//�����ص�
	inline virtual void afterDead();
};





#endif 