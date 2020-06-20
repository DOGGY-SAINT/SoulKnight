#ifndef _WEAPON_H_
#define _WEAPON_H_
#include"Actor/Bullet.h"
#include"cocos2d.h"
#include"Actor/Actor.h"
#include"Actor/Hero.h"
#include"Actor/MovingActor.h"
USING_NS_CC;

//Weapon���Կ��Ǵ���Bullet���ֻ�����ô��
class Weapon :
	public Actor
{

	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletData, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
	CC_SYNTHESIZE(bool, _on, IsOn);
	CC_SYNTHESIZE(int, _powerCost, PowerCost);
protected:
	Vec2 _direction;
public:
	bool onContactBegin(Actor* a2)override;

	bool weaponOffContact(Actor*);

	bool weaponOnContact(Actor*);


	Vec2 getDirection() { return _direction; }

	void setDirection(Vec2 dir) { _direction = dir; updateRotation(); }

	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName, ValueMap valueMap);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//��������
	virtual void weaponOn(MovingActor* myHero);

	//��������
	virtual void weaponOff();

	//���ι���
	virtual void attack(float dt);

	void bitMaskOn();

	void bitMaskOff();

	void updateNohurt(float dt);
};

//�趨��delay
inline void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}




#endif