#ifndef _SINGLESHOTGUN_H_
#define _SINGLESHOTGUN_H_
#include "Weapon.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class SingleShotgun :
	public Weapon
{
public:
	SingleShotgun();
	~SingleShotgun();
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static SingleShotgun* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//��������,δ���
	//virtual void weaponOn();

	//����������δ���
	//virtual void weaponOff();

	//����������
	virtual inline void onLeftPressed();

	//�ɿ�������
	virtual inline void onLeftReleased();

	//���ι���
	virtual void attack(float dt);
};

inline void SingleShotgun::onLeftPressed()
{
	schedule(schedule_selector(SingleShotgun::attack), _gapTime, CC_REPEAT_FOREVER, _gapTime);
}

inline void SingleShotgun::onLeftReleased()
{
	unschedule(schedule_selector(SingleShotgun::attack));
}

inline void SingleShotgun::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}
#endif
