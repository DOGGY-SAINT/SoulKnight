#ifndef __secondScene_H__
#define __secondScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class secondScene :public cocos2d::Scene
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(secondScene);
};

#endif 