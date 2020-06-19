#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_
#include "Weapon.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class Shotgun :
	public Weapon
{
public:
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static Shotgun* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//��������,δ���
	//virtual void weaponOn();

	//����������δ���
	//virtual void weaponOff();

	virtual void update(float dt);

	//���ι���,δʵ��
	virtual void attack(float dt);
};


inline void Shotgun::updateRotation()
{
	setFlipY(_direction.x <= 0);
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}

#endif