#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

//Weapon���Կ��Ǵ���Bullet���ֻ�����ô��
class Weapon :
	public Actor
{
	
	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletDate, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
	CC_SYNTHESIZE(Vec2, _direction, Direction);

	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation(float dt);

	//��������,δ���
	virtual void weaponOn();

	//����������δ���
	virtual void weaponOff();

	//����������
	inline void onLeftPressed();

	//�ɿ�������
	inline void onLeftReleased();

	//���ι���,δʵ��
	virtual void attack(float dt) {};
};

//�趨��delay
inline void Weapon::onLeftPressed()
{
	schedule(schedule_selector(Weapon::attack),_gapTime, CC_REPEAT_FOREVER, _gapTime);
	
}

inline void Weapon::onLeftReleased()
{
	unschedule(schedule_selector(Weapon::attack));
}

inline void Weapon::updateRotation(float dt)
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}




#endif