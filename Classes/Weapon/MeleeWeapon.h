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

	//����������
	inline void onLeftPressed();

	//�ɿ�������
	inline void onLeftReleased();

	//���ι���
	virtual void attack(float dt);
};


inline void MeleeWeapon::onLeftPressed()
{
	schedule(schedule_selector(MeleeWeapon::attack), _gapTime*1.5, CC_REPEAT_FOREVER, _gapTime*1.5);
}

inline void MeleeWeapon::onLeftReleased()
{
	unschedule(schedule_selector(MeleeWeapon::attack));
}

inline void MeleeWeapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}
#endif
