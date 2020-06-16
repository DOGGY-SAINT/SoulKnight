#include "MapLayer.h"
#include "Actor\Actor.h"
<<<<<<< HEAD
#include"Component\Constant.h"
#include"MainScene.h"
#include"Weapon/Weapon.h"
#include"Weapon/SingleShotgun.h"
#include"Weapon/Shotgun.h"
#include"Weapon/MeleeWeapon.h"
using namespace std;
=======
#include"Actor/Hero.h"
#include"Component\Constant.h"
#include"MainScene.h"
#include"Actor/MapPortal.h"
#include"Actor/Box.h"
#include"Weapon/Weapon.h"
#include<algorithm>

//#define INITLAYER(layerName)\
//init##layerName##Layer()
>>>>>>> DOGGY_LEE

MapLayer* MapLayer::create(std::string mapName)
{
	MapLayer *map = new (std::nothrow) MapLayer();
	if (map->init(mapName))
	{
		map->autorelease();
		return map;
	}
	CC_SAFE_DELETE(map);
	return nullptr;
}

bool MapLayer::init(std::string mapName)
{
	if (!Layer::create())
		return false;
<<<<<<< HEAD
	initMap(mapName);
	initTile();
	/*initObject();*/

    //tmp
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto weaponPlist = CCSpriteFrameCache::sharedSpriteFrameCache();
	weaponPlist->addSpriteFramesWithFile(PATH_DATA + "WeaponData.plist", PATH_PICTURE_WEAPON + "WeaponData.png");
	auto lable = LabelTTF::create("tmp", "Arial", 20);
	lable->setPosition(500, 100);
	this->addChild(lable, 6);
	string mstr0 = "Mouse.x:";
	string mstr1 = "Mouse.y";
	string wstr0 = "Weapon.x:";
	string wstr1 = "Weapon.y:";
	MeleeWeapon* lightsaber = MeleeWeapon::createWithName("lightsaber");

	SingleShotgun* pistol = SingleShotgun::createWithName("pistol");
	//MeleeWeapon* lightsaber = MeleeWeapon::createWithName("lightsaber");
	pistol->setPosition(200, 200);
	lightsaber->setPosition(200, 200);
	this->addChild(pistol);
	this->addChild(lightsaber);

	mainWeapon = pistol;
	mainWeapon->setLocalZOrder(6);
	secondaryWeapon = lightsaber;
	secondaryWeapon->setLocalZOrder(-1);

	auto wpos = pistol->getPosition();
	string wstr = wstr0 + to_string(wpos.x) + wstr1 + to_string(wpos.y);

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event* event){
		if (code == EventKeyboard::KeyCode::KEY_Q) {
			mainWeapon->onLeftReleased();
			Weapon* change=mainWeapon;
			mainWeapon = secondaryWeapon;
			secondaryWeapon = change;
			mainWeapon->setLocalZOrder(6);
			secondaryWeapon->setLocalZOrder(-1);
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [=](EventMouse* event) {
		auto tmp = event->getLocation();
		tmp.y = visibleSize.height - tmp.y;
		auto mpos = tmp;
		string mstr = mstr0 + to_string(mpos.x) + mstr1 + to_string(mpos.y);
		lable->setString(mstr + "    " + wstr);
		/*pistol->setDirection(tmp-pistol->getPosition());
		lightsaber->setDirection(tmp - pistol->getPosition());
		pistol->updateRotation();
		lightsaber->updateRotation();*/
		mainWeapon->setDirection(tmp - pistol->getPosition());
		mainWeapon->updateRotation();
	};
	mouseListener->onMouseDown = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			mainWeapon->onLeftPressed();
			
		}
	};
	mouseListener->onMouseUp = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			mainWeapon->onLeftReleased();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	return true;
}

void MapLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

}

void MapLayer::initMap(std::string mapName)
{
	_tiledMap = TMXTiledMap::create(PATH_MAP + mapName+".tmx");
	CCASSERT(_tiledMap, "Map Not Found");
}

void MapLayer::initTile()
=======
	MainScene::SharedScene()->setMapLayer(this);
	initMap(mapName);
	initTileLayer();
	initObjectLayer();
	return true;
}

void MapLayer::initMap(std::string mapName)
{
	_tiledMap = TMXTiledMap::create(PATH_MAP + mapName + ".tmx");
	CCASSERT(_tiledMap, "Map Not Found");
}

void MapLayer::initTileLayer()
>>>>>>> DOGGY_LEE
{
	auto children = _tiledMap->getChildren();
	for (auto& child : children)
	{
		auto layer = dynamic_cast<TMXLayer*>(child);
		if (layer)
		{
			auto LayerProperties = layer->getProperties();
			auto layerSize = layer->getLayerSize();
			//遍历瓦片
			for (int i = 0; i < layerSize.height; i++)
			{
				for (int j = 0; j < layerSize.width; j++)
				{
					auto tile = layer->getTileAt(Vec2(i, j));
<<<<<<< HEAD
					
=======

>>>>>>> DOGGY_LEE
					if (tile)
					{
						auto size = tile->getContentSize();
						/*auto gid = layer->getTileGIDAt(Vec2(i, j));
						auto tileProperties = _tiledMap->getPropertiesForGID(gid).asValueMap();*/
						/*auto rect = layer->getTileSet()->getRectForGID(gid);*/
						auto actor = Actor::createWithSprite(tile, LayerProperties);//物理body在这里实现
						this->addChild(actor);
					}
				}
			}

		}
	}
}

<<<<<<< HEAD

inline Vec2 MapLayer::TileSpaceToNodeSpace(float x, float y)
{
	auto map = MainScene::SharedScene()->getMyMapLayer()->getTiledMap();
	Size tileSize = map->getTileSize();
	Size mapSize = map->getMapSize();
	float height = tileSize.height * mapSize.height;
	return Vec2(x, height - y);
=======
void MapLayer::initObjectLayer()
{
	initBornLayer();
	initMapPortalLayer();
	initBoxLayer();
}

void MapLayer::initMapPortalLayer()
{
	auto layer = _tiledMap->getObjectGroup("MapPortalLayer");
	auto Group = layer->getObjects();
	for (auto obj : Group)
	{
		auto valueMap = obj.asValueMap();
		auto portal = MapPortal::createWithObject(valueMap);
		addChild(portal);
	}
}

void MapLayer::initBoxLayer()
{
	auto layer = _tiledMap->getObjectGroup("BoxLayer");
	auto Group = layer->getObjects();
	for (auto obj : Group)
	{
		auto valueMap = obj.asValueMap();
		auto box = Box::createWithObject(valueMap);
		addChild(box);
	}
}

//object所获得的x与y已经自动转换成cocos2dx中的坐标
void MapLayer::initBornLayer()
{
	auto layer = _tiledMap->getObjectGroup("BornLayer");
	auto valueMap = layer->getObject("BornPlace");

	float x = VALUE_AT(valueMap, "x", Float), y = VALUE_AT(valueMap, "y", Float);
	_bornPlace = Vec2(x, y);
>>>>>>> DOGGY_LEE
}

Vec2 MapLayer::getObjectNodeSpace(ValueMap valueMap)
{
<<<<<<< HEAD
	auto map = MainScene::SharedScene()->getMyMapLayer()->getTiledMap();
	Size tileSize = map->getTileSize();
	Size mapSize = map->getMapSize();
	float mapHeight = tileSize.height * mapSize.height;
	float height = VALUE_AT(valueMap, "height", Float);
	auto x = VALUE_AT(valueMap, "x", Float), y = VALUE_AT(valueMap, "y", Float);
	return Vec2(x, mapHeight - y - height);
=======
	float height = VALUE_AT(valueMap, "height", Float);
	auto x = VALUE_AT(valueMap, "x", Float), y = VALUE_AT(valueMap, "y", Float);
	return Vec2(x, y + height);
}

void MapLayer::releaseAllWeapon()
{
	for (auto weapon : toRelease)
		weapon->release();
}

void MapLayer::addHero(Hero* hero)
{
	addChild(hero);
	setHero(hero);
	hero->setPosition(_bornPlace);
}

void MapLayer::addWeaponToVec(Weapon *weapon)
{
	auto it = std::find(toRelease.begin(), toRelease.end(), weapon);
	if (it == toRelease.end())
		toRelease.insert(it,weapon);
}

void MapLayer::removeWeaponFromVec(Weapon *weapon)
{
	auto it = std::find(toRelease.begin(), toRelease.end(), weapon);
	if (it != toRelease.end())
		toRelease.erase(it);
>>>>>>> DOGGY_LEE
}
