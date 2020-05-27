#ifndef _BULLET_H_
#define _BULLET_H_
#include"cocos2d.h"
USING_NS_CC;
class Bullet :public cocos2d::Sprite
{
    public:
		virtual bool init();
		virtual void shootingMode()=0;
		virtual int getBulletAmount()=0;
   //protected:
		int bulletAmount;
		Sprite* bulletShape;
};


#endif
