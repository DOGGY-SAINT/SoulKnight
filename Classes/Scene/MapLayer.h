#pragma once
#include"cocos2d.h"
#include<vector>
class Hero;
class PauseLayer;
class Weapon;

USING_NS_CC;
class MapLayer :public Layer
{
	CC_SYNTHESIZE(Vec2, _bornPlace, BornPlace);
	CC_SYNTHESIZE(Hero*, _hero, Hero);
	CC_SYNTHESIZE(TMXTiledMap*, _tiledMap, TiledMap);
private:
	void initMap(std::string mapName);

	void initTileLayer();

	void initObjectLayer();

	void initBornLayer();

	void initMapPortalLayer();

	void initBoxLayer();
public:
	std::vector<Weapon*> toRelease;

	static MapLayer* create(std::string mapName);

	virtual bool init(std::string mapName);

	static Vec2 TileSpaceToNodeSpace(float x, float y, TMXTiledMap*);

	static Vec2 getObjectNodeSpace(ValueMap);

	void releaseAllWeapon();

	void addHero(Hero*);

	void addWeaponToVec(Weapon*);

	void removeWeaponFromVec(Weapon*);

};