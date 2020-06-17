#ifndef _HERO_H_
#define _HERO_H_

#include"cocos2d.h"
#include"MovingActor.h"
USING_NS_CC;
class Weapon;

//hero��Ҫ�ֶ�release
class Hero
	:public MovingActor
{
protected:
	//����
	State _AC;
	//����
	State _power;
	//�ǲ��ǵ���
	CC_SYNTHESIZE(bool, _on, IsOn);
	CC_SYNTHESIZE(bool, _wPressed, WPressed);
	CC_SYNTHESIZE(bool, _aPressed, APressed);
	CC_SYNTHESIZE(bool, _sPressed, SPressed);
	CC_SYNTHESIZE(bool, _dPressed, DPressed);
	CC_SYNTHESIZE(Weapon*, _weaponToOn, WeaponToOn);
	CC_SYNTHESIZE(Hero*, _heroToOn, HeroToOn);
	std::vector<Weapon*> _weaponVector;
public:
	static const PhysicsMaterial defaultMaterial;

	static Hero* createWithName(std::string);

	virtual bool initWithName(std::string);

	static Hero* createWithObject(ValueMap);

	virtual bool initWithObject(ValueMap);

	void initData(ValueMap)override;

	void initCollision(ValueMap)override;

	//��ʼ��HP��AC��Power�������Զ��ָ�
	void initState(ValueMap);

	//wasd��ʼ��
	void initController();

	void initScheduler();

	void removeScheduler();

	//update
	void updateHP(float dt);

	void updateAC(float dt);

	void updatePower(float dt);

	void updateV(float dt);

	void changeWeapon();

	void getHurt(INT32 dmg)override;

	State* getAC() { return &_AC; }

	State* getPower() { return &_power; }

	bool onContactBegin(Actor*)override;

	bool onContactSeparate(Actor*)override;

	bool heroOnContact(Actor*);

	bool heroOffContact(Actor*);

	void heroOn();

	void heroOff();

};

//��ʼ���������ָ�




#endif 