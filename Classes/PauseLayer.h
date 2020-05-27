
#ifndef _PAUSE_LAYER_H_
#define _PAUSE_LAYER_H_
#include"cocos2d.h"

class PauseLayer :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PauseLayer);


};




#endif#pragma once
