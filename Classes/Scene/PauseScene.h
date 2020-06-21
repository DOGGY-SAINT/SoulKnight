#ifndef _PAUSE_SCENE_H_
#define _PAUSE_SCENE_H_
#include"cocos2d.h"
#include "SimpleAudioEngine.h"

class PauseScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void initKeyBoardListener();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);


};



#endif