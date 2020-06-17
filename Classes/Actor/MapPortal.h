#pragma once
#include"cocos2d.h"
#include"Actor/Actor.h"
USING_NS_CC;
class MapPortal
	:public Actor
{
	CC_SYNTHESIZE(std::string, _nextMap, NextMap);
private:
	void initData(ValueMap)override;
public:
	static MapPortal* createWithObject(ValueMap);

	bool onContactBegin(Actor*)override;

	bool onContactSeparate(Actor*)override;

	void changeMap();

	

};
