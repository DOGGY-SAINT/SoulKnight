#pragma once
#include"cocos2d.h"
#include<vector>
class Hero;
class PauseLayer;
class Weapon;
class Actor;

USING_NS_CC;
class MapLayer :public Layer
{
	CC_SYNTHESIZE(Vec2, _bornPlace, BornPlace);
	CC_SYNTHESIZE(TMXTiledMap*, _tiledMap, TiledMap);
private:
	void initMap(std::string mapName);

	void initTileLayer();

	void initObjectLayer();

	void initBornLayer();

	void initMapPortalLayer();

	void initBoxLayer();

	void initMonsterLayer();

	void initHeroLayer();
public:
	std::vector<Actor*> toRelease;

	static MapLayer* create(std::string mapName);

	virtual bool init(std::string mapName);

	static Vec2 getObjectNodeSpace(ValueMap);

	void releaseAllActor();

	void addHero(Hero*);

	void addActorToVec(Actor * actor);

	void removeActorFromVec(Actor * actor);

};