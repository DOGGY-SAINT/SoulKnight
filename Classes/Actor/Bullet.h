#ifndef _BULLET_H_
#define _BULLET_H_
#include"cocos2d.h"
#include"Actor.h"
USING_NS_CC;

class Bullet
	:public Actor
{
public:
	//纹理初始化
	static Bullet* createByTexture(Texture2D*, ValueMap);

	//纹理初始化
	bool initByTexture(Texture2D*, ValueMap);

	inline void getHurt(INT32 dmg)override;
};

inline void Bullet::getHurt(INT32 dmg)
{
	_HP.setStateBy(-1);
}

#endif