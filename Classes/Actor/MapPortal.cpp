#include "MapPortal.h"
#include"Component/Constant.h"
#include"Scene/MainScene.h"


void MapPortal::initData(ValueMap valueMap)
{
	SET_DATA(valueMap, CanBeHurt, Bool);
	SET_DATA(valueMap, Damage, Int);
	SET_DATA(valueMap, LocalZOrder, Int);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, Flag, Int);
	_HP = State(VALUE_AT(valueMap, "HP", Int));

	SET_DATA(valueMap, NextMap, String);
}

MapPortal* MapPortal::createWithObject(ValueMap valueMap)
{
	MapPortal* mapPortal = new(std::nothrow)MapPortal;
	if (mapPortal && mapPortal->initWithObject(valueMap))
	{
		mapPortal->autorelease();
		return mapPortal;
	}
	CC_SAFE_DELETE(mapPortal);
	return nullptr;
}


bool MapPortal::onContactBegin(Actor* actor)
{
	if (actor->getName() == "Hero")
		MainScene::SharedScene()->onRPressed = CC_CALLBACK_0(MapPortal::changeMap, this);
	return false;
}

bool MapPortal::onContactSeparate(Actor *)
{
	MainScene::SharedScene()->onRPressed = nullptr;
	return false;
}

void MapPortal::changeMap()
{
	MainScene::SharedScene()->changeMap(_nextMap);
	MainScene::SharedScene()->onRPressed = nullptr;
}