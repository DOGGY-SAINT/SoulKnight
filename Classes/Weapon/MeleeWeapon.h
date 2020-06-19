#ifndef _MELEEWEAPON_H_
#define _MELEEWEAPON_H_
#include "Weapon.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class MeleeWeapon :
	public Weapon
{
public:
	MeleeWeapon();
	~MeleeWeapon();
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static MeleeWeapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//��������,δ���
	//virtual void weaponOn();

	//����������δ���
	//virtual void weaponOff();

	virtual void update(float dt);

	//���ι���
	virtual void attack(float dt)override;
};

inline void MeleeWeapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}
#endif
