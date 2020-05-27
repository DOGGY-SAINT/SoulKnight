#pragma once
#ifndef __secondScene_H__
#define __secondScene_H__
<<<<<<< HEAD

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

=======
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
>>>>>>> Kite
class secondScene :public cocos2d::Scene
{
public:
	virtual bool init();
<<<<<<< HEAD
	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(secondScene);
=======
	virtual void update(float dt);
	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	//void onMousePressedUpdate(float dt);
	void onMousePressed(float dt);
	void onMouseMove(EventMouse *e);
	// implement the "static create()" method manually
	CREATE_FUNC(secondScene);
	Vec2 dir;
>>>>>>> Kite
};

#endif 
#pragma once
