#include "MapLayer.h"
#include "Actor\Actor.h"
#include"Component\Constant.h"
#include"MainScene.h"

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
	initMap(mapName);
	initTile();
	/*initObject();*/
	return true;
}

void MapLayer::initMap(std::string mapName)
{
	_tiledMap = TMXTiledMap::create(PATH_MAP + mapName+".tmx");
	CCASSERT(_tiledMap, "Map Not Found");
}

void MapLayer::initTile()
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

inline Vec2 MapLayer::TileSpaceToNodeSpace(float x, float y)
{
	auto map = MainScene::SharedScene()->getMyMapLayer()->getTiledMap();
	Size tileSize = map->getTileSize();
	Size mapSize = map->getMapSize();
	float height = tileSize.height * mapSize.height;
	return Vec2(x, height - y);
}

Vec2 MapLayer::getObjectNodeSpace(ValueMap valueMap)
{
	auto map = MainScene::SharedScene()->getMyMapLayer()->getTiledMap();
	Size tileSize = map->getTileSize();
	Size mapSize = map->getMapSize();
	float mapHeight = tileSize.height * mapSize.height;
	float height = VALUE_AT(valueMap, "height", Float);
	auto x = VALUE_AT(valueMap, "x", Float), y = VALUE_AT(valueMap, "y", Float);
	return Vec2(x, mapHeight - y - height);
}
