#ifndef _WEAPON_H_
#define _WEAPON_H_
#include"Actor/Bullet.h"
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

    public:
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	virtual bool initWithName(std::string weaponName)=0;

	virtual void initWithValueMap(ValueMap)=0;

	virtual void initBulletData(ValueMap)=0;

	virtual inline void updateRotation();

	//��������
	virtual void weaponOn();

	//��������
	virtual void weaponOff();

	//���ι���
	virtual void attack(float dt)=0;
};

//�趨��delay
inline void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}




#endif