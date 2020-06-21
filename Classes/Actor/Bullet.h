#ifndef _BULLET_H_
#define _BULLET_H_
#include"cocos2d.h"
#include"Actor.h"
USING_NS_CC;

class Bullet
	:public Actor
{
public:
	//�����ʼ��
	static Bullet* createByTexture(Texture2D*, ValueMap);

	//�����ʼ��
	bool initByTexture(Texture2D*, ValueMap);

	inline void getHurt(INT32 dmg)override;
};

inline void Bullet::getHurt(INT32 dmg)
{
	_HP.setStateBy(-1);
}

#endif