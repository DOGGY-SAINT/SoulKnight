#pragma once
#include"cocos2d.h"
class Hero;
class PauseLayer;


USING_NS_CC;
class MapLayer:public Layer
{
private:
	CC_SYNTHESIZE(Vec2, _bornPlace, BornPlace);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(TMXTiledMap*, _tiledMap, TiledMap);
public:

	static MapLayer* create(std::string mapName);

	virtual bool init(std::string mapName);

	static Vec2 TileSpaceToNodeSpace(float x,float y);

	static Vec2 getObjectNodeSpace(ValueMap);

	void initMap(std::string mapName);

	void initTile();

	void initObject();

	void addHero(Hero*,Vec2);

};