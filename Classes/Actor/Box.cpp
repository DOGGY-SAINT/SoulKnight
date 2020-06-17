#include "Box.h"
#include"Scene/MainScene.h"
#include"RecoverProp.h"
#include"Weapon/Weapon.h"
#include"Weapon/MeleeWeapon.h"
#include"Weapon/Shotgun.h"
#include"Weapon/SingleShotgun.h"
#include"Scene/MapLayer.h"
#include<time.h>
#include<stdlib.h>

Box * Box::createWithObject(ValueMap valueMap)
{
	Box* box = new(std::nothrow)Box;
	if (box && box->initWithObject(valueMap))
	{
		box->autorelease();
		return box;
	}
	CC_SAFE_DELETE(box);
	return nullptr;
}

bool Box::initWithObject(ValueMap valueMap)
{
	if (!initWithFile(VALUE_AT(valueMap, "TexturePath", String)))
		return false;
	setAnchorPoint(Vec2::ZERO);
	auto position = MapLayer::getObjectNodeSpace(valueMap);
	setPosition(position);
	initData(valueMap);
	initCollision(valueMap);
	_open = false;
	randAllProp();
	return true;
}

void Box::randAllProp()
{
	srand(time(0));
	auto n = rand();
	auto file = FileUtils::getInstance();
	if (n % 2)
		randProp(file->getValueMapFromFile(PATH_DATA + "PropData.plist"));
	else
		randWeapon(file->getValueMapFromFile(PATH_DATA + "WeaponData.plist"));
}

void Box::randProp(ValueMap valueMap)
{
	_prop = nullptr;
	for (auto map : valueMap)
	{
		auto n = rand();
		if (n % 2)
		{
			_prop = RecoverProp::createWithName(map.first);
			MainScene::SharedScene()->getMapLayer()->addChild(_prop, 100);
			_prop->setPosition(getPosition());
			_prop->getPhysicsBody()->setEnabled(false);
			_prop->setVisible(false);
			return;
		}
	}
}

void Box::randWeapon(ValueMap valueMap)
{
	_prop = nullptr;
	for (auto map : valueMap)
	{
		auto n = rand();
		if (n)
		{
			//_prop = Weapon::createWithName(map.first);
			_prop = SingleShotgun::createWithName(map.first);
			MainScene::SharedScene()->getMapLayer()->addChild(_prop, 100);
			_prop->setPosition(getPosition());
			if (_prop->getPhysicsBody())
				_prop->getPhysicsBody()->setEnabled(false);
			_prop->setVisible(false);
			return;
		}
	}
}


bool Box::onContactBegin(Actor *a2)
{
	if ((!isOpen()) && a2->getName() == "Hero")
		MainScene::SharedScene()->onRPressed = CC_CALLBACK_0(Box::openBox, this);
	return false;
}

bool Box::onContactSeparate(Actor *a2)
{
	if ((!isOpen()) && a2->getName() == "Hero")
		MainScene::SharedScene()->onRPressed = nullptr;
	return false;
}

void Box::openBox()
{
	_open = true;
	if (_prop)
	{
		_prop->setVisible(true);
		if (_prop->getPhysicsBody())
			_prop->getPhysicsBody()->setEnabled(true);
	}
	MainScene::SharedScene()->onRPressed = nullptr;
	afterDead();
}

