#include "MapLayer.h"
#include "Actor\Actor.h"
#include"Actor/Hero.h"
#include"Component\Constant.h"
#include"MainScene.h"
#include"Actor/MapPortal.h"
#include"Actor/Box.h"

//#define INITLAYER(layerName)\
//init##layerName##Layer()

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
		auto portal=MapPortal::createWithObject(valueMap);
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
}

//inline Vec2 MapLayer::TileSpaceToNodeSpace(float x, float y, TMXTiledMap* map)
//{
//	auto scene = MainScene::SharedScene();
//	Size tileSize = map->getTileSize();
//	Size mapSize = map->getMapSize();
//	float height = tileSize.height * mapSize.height;
//	return Vec2(x, height - y);
//}

Vec2 MapLayer::getObjectNodeSpace(ValueMap valueMap)
{
	float height = VALUE_AT(valueMap, "height", Float);
	auto x = VALUE_AT(valueMap, "x", Float), y = VALUE_AT(valueMap, "y", Float);
	return Vec2(x,y + height);
}

void MapLayer::addHero(Hero* hero)
{
	addChild(hero);
	setHero(hero);
	hero->setPosition(_bornPlace);	
}
