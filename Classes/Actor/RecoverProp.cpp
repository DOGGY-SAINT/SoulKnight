#include "RecoverProp.h"
#include"Scene/MainScene.h"
#include"Actor/Hero.h"

RecoverProp * RecoverProp::createWithName(std::string name)
{
	RecoverProp* prop = new(std::nothrow)RecoverProp;
	if (prop && prop->initWithName(name))
	{
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}

bool RecoverProp::initWithName(std::string name)
{
	if (!initWithFile(PATH_PICTURE_PROP + name + ".png"))
		return false;
	auto file = FileUtils::getInstance();
	auto map = file->getValueMapFromFile(PATH_DATA + "PropData.plist");
	auto thisMap = map[name].asValueMap();
	auto defaultMap= file->getValueMapFromFile(PATH_DATA + "PropDefaultData.plist");
	initData(VALUE_AT(defaultMap,"CommonData",ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));
	initOther(thisMap);
	return true;
}

void RecoverProp::initOther(ValueMap valueMap)
{
	auto type = VALUE_AT(valueMap,"Type",String);
	if (type == "HP")
		_type = HP;
	else if (type == "Power")
		_type = Power;
	SET_DATA(valueMap,RecoverNum,Int);
}

bool RecoverProp::onContactBegin(Actor *a2)
{
	if (a2->getName() == "Hero")
		MainScene::SharedScene()->onRPressed = CC_CALLBACK_0(RecoverProp::recover,this);
	return false;
}

void RecoverProp::recover()
{
	State* state;
	if (_type == HP)
		state = MainScene::SharedScene()->getHero()->getHP();
	else if(_type==Power)
		state = MainScene::SharedScene()->getHero()->getPower();
	state->setStateBy(_recoverNum);
	afterDead();
}
