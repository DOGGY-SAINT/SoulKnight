#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;

class MovingActor;

//Weapon可以考虑储存Bullet名字或者怎么样
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
	//这里考虑武器信息都在plist内，因此用name初始化，后续可以考虑load时创造instance然后这里直接copy
	static Weapon* createWithName(std::string weaponName);

	virtual bool initWithName(std::string weaponName);

	virtual void initWithValueMap(ValueMap);

	virtual void initBulletData(ValueMap);

	virtual inline void updateRotation();

	//拿上武器,未完成
	virtual void weaponOn(MovingActor*);

	//换下武器，未完成
	virtual void weaponOff();

	//按下鼠标左键
	inline void onLeftPressed();

	//松开鼠标左键
	inline void onLeftReleased();

	//单次攻击,未实现
	virtual void attack(float dt) {};

	bool onContactBegin(Actor* a2)override;

	bool weaponOffContact(Actor*);

	bool weaponOnContact(Actor*);

	Vec2 getDirection() { return _direction; }

	void setDirection(Vec2 dir);

};


#endif