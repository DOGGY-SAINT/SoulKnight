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
		virtual bool init();//将武器界面和武器位置初始化 
		void update(float dt);//包括武器位置更新，界面内武器信息的更新，       子弹数更新写在Bullet内 
		//virtual bool changeWeapon();//判断是否要切换武器，即最大武器数为2
		//virtual int getBulletAmount();
		//virtual string getWeaponName();
		//virtual bool mouseMonitor(EventMouse *e);//判断是否射击也就是鼠标控制 
		 Vec2 getWeaponPos();
		//void onMouseMove(EventMouse *e);
		//Sprite* getSpriteShape();
		CREATE_FUNC(Pistol);
    //private:
		PistolBullet* bullet;
		Sprite* spriteShape;
};


#endif