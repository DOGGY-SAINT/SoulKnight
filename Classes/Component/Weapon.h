#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
USING_NS_CC;
#include"Bullet.h"
#include <iostream>
#include <string>
using namespace std;
//Weapon���Կ��Ǵ���Bullet���ֻ�����ô��
class Weapon :public cocos2d::Sprite 
{
	public:
		virtual bool init();//���������������������λ�ó�ʼ�� 
		virtual void update(float dt)=0;//��������λ�ø��£�������������Ϣ�ĸ��£�       �ӵ�������д��Bullet�� 
		//virtual bool changeWeapon()=0;//�ж��Ƿ�Ҫ�л������������������Ϊ2
		//virtual int getBulletAmount()=0;
		//virtual string getweaponName()=0;
		virtual Vec2 getWeaponPos()=0;
	//protected:
		string weaponName;
		Sprite* weaponShape;
};

#endif
