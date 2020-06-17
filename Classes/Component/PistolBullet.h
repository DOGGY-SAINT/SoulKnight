#ifndef _PISTOLBULLET_H_
#define _PISTOLBULLET_H_
#include"cocos2d.h"
USING_NS_CC;
#include "Bullet.h"
class PistolBullet :public Bullet
{
public:
	PistolBullet();
	~PistolBullet();
	virtual bool init();
	virtual void shootingMode();
	virtual int getBulletAmount();
	CREATE_FUNC(PistolBullet);
	int bulletAmount;
//private:
	Sprite* pistolBulletShape;
};

#endif