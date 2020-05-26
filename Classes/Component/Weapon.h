#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
USING_NS_CC;
#include"Bullet.h"
#include <iostream>
#include <string>
using namespace std;
//Weapon可以考虑储存Bullet名字或者怎么样
class Weapon :public cocos2d::Sprite 
{
	public:
		virtual bool init();//将武器，武器界面和武器位置初始化 
		virtual void update(float dt)=0;//包括武器位置更新，界面内武器信息的更新，       子弹数更新写在Bullet内 
		//virtual bool changeWeapon()=0;//判断是否要切换武器，即最大武器数为2
		//virtual int getBulletAmount()=0;
		//virtual string getweaponName()=0;
		virtual Vec2 getWeaponPos()=0;
	//protected:
		string weaponName;
		Sprite* weaponShape;
};

#endif
