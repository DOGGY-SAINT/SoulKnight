#pragma once
#include"cocos2d.h"
<<<<<<< HEAD
#include"Weapon/Weapon.h"
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
=======
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
>>>>>>> DOGGY_LEE

	static MapLayer* create(std::string mapName);

	virtual bool init(std::string mapName);

<<<<<<< HEAD
	static Vec2 TileSpaceToNodeSpace(float x,float y);

	static Vec2 getObjectNodeSpace(ValueMap);

	void initMap(std::string mapName);

	void initTile();

	void initObject();

	void addHero(Hero*,Vec2);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	Weapon* mainWeapon;
	Weapon* secondaryWeapon;
=======
	static Vec2 TileSpaceToNodeSpace(float x, float y, TMXTiledMap*);

	static Vec2 getObjectNodeSpace(ValueMap);

	void releaseAllWeapon();

	void addHero(Hero*);

	void addWeaponToVec(Weapon*);

	void removeWeaponFromVec(Weapon*);

>>>>>>> DOGGY_LEE
};