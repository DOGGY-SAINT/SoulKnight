#ifndef _WEAPON_H_
#define _WEAPON_H_
<<<<<<< HEAD
#include"Actor/Bullet.h"
=======

>>>>>>> DOGGY_LEE
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

<<<<<<< HEAD
=======
class MovingActor;

>>>>>>> DOGGY_LEE
//Weapon���Կ��Ǵ���Bullet���ֻ�����ô��
class Weapon :
	public Actor
{
	
	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletDate, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
<<<<<<< HEAD
	CC_SYNTHESIZE(Vec2, _direction, Direction);

    public:
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	virtual bool initWithName(std::string weaponName)=0;

	virtual void initWithValueMap(ValueMap)=0;

	virtual void initBulletData(ValueMap)=0;
=======
	CC_SYNTHESIZE(bool, _on, IsOn);
private:
	Vec2 _direction;
public:
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);
>>>>>>> DOGGY_LEE

	virtual inline void updateRotation();

	//��������,δ���
<<<<<<< HEAD
	virtual void weaponOn();
=======
	virtual void weaponOn(MovingActor*);
>>>>>>> DOGGY_LEE

	//����������δ���
	virtual void weaponOff();

	//����������
<<<<<<< HEAD
	virtual inline void onLeftPressed();

	//�ɿ�������
	virtual inline void onLeftReleased();

	//���ι���,δʵ��
	virtual void attack(float dt)=0;
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

inline void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}


=======
	inline void onLeftPressed();

	//�ɿ�������
	inline void onLeftReleased();

	//���ι���,δʵ��
	virtual void attack(float dt) {};

	bool onContactBegin(Actor* a2)override;

	bool weaponOffContact(Actor*);

	bool weaponOnContact(Actor*);

	Vec2 getDirection() { return _direction; }

	void setDirection(Vec2 dir);

};
>>>>>>> DOGGY_LEE


#endif