#ifndef _PISTOL_H_
#define _PISTOL_H_
#include"cocos2d.h"
USING_NS_CC;
#include"Bullet.h"
#include <iostream>
#include "Weapon.h"
#include"PistolBullet.h"
using namespace std;
class Pistol :public Weapon
{
     public:
	    Pistol();
	    ~Pistol();
		virtual bool init();//���������������λ�ó�ʼ�� 
		void update(float dt);//��������λ�ø��£�������������Ϣ�ĸ��£�       �ӵ�������д��Bullet�� 
		//virtual bool changeWeapon();//�ж��Ƿ�Ҫ�л������������������Ϊ2
		//virtual int getBulletAmount();
		//virtual string getWeaponName();
		//virtual bool mouseMonitor(EventMouse *e);//�ж��Ƿ����Ҳ���������� 
		 Vec2 getWeaponPos();
		//void onMouseMove(EventMouse *e);
		//Sprite* getSpriteShape();
		CREATE_FUNC(Pistol);
    //private:
		PistolBullet* bullet;
		Sprite* spriteShape;
};


#endif