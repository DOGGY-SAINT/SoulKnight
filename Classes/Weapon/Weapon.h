#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

class MovingActor;

//Weapon���Կ��Ǵ���Bullet���ֻ�����ô��
class Weapon :
	public Actor
{
	
	CC_SYNTHESIZE(float, _gapTime, GapTime);
	CC_SYNTHESIZE(ValueMap, _bulletDate, BulletData);
	CC_SYNTHESIZE(Texture2D*, _bulletTexture, BulletTexture);
	CC_SYNTHESIZE(bool, _on, IsOn);
private:
	Vec2 _direction;
public:
	//���￼��������Ϣ����plist�ڣ������name��ʼ�����������Կ���loadʱ����instanceȻ������ֱ��copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//��������,δ���
	virtual void weaponOn(MovingActor*);

	//����������δ���
	virtual void weaponOff();

	//����������
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


#endif