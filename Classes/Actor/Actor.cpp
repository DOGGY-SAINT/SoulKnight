#include "Actor.h"
#include"Scene/MapLayer.h"
#include"Component/Constant.h"
#include"Scene/MainScene.h"



Actor* Actor::createWithSprite(Sprite* sp, ValueMap valueMap)
{
	Actor* actor = new(std::nothrow)Actor;
	if (actor && actor->initWithSprite(sp, valueMap))
	{
		actor->autorelease();
		return actor;
	}
	CC_SAFE_DELETE(actor);
	return nullptr;
}

bool Actor::initWithSprite(Sprite* sp, ValueMap valueMap)
{
	auto rect = sp->getTextureRect();
	if (!initWithTexture(sp->getTexture(), sp->getTextureRect()))
		return false;
	auto size = getContentSize();
	setAnchorPoint(Vec2::ZERO);
	auto position = sp->getPosition();
	setPosition(sp->getPosition());
	initData(valueMap);
	initCollision(valueMap);
	return true;
}

//对象初始化
Actor* Actor::createWithObject(ValueMap valueMap)
{
	Actor* actor = new(std::nothrow)Actor;
	if (actor && actor->initWithObject(valueMap))
	{
		actor->autorelease();
		return actor;
	}
	CC_SAFE_DELETE(actor);
	return nullptr;
}

//对象初始化
bool Actor::initWithObject(ValueMap valueMap)
{
	if (!initWithFile(VALUE_AT(valueMap, "TexturePath", String)))
		return false;
	setAnchorPoint(Vec2::ZERO);
	/*auto x= VALUE_AT(valueMap, "x", Float), y = MapLayer::getObjectNodeSpace(valueMap,MainScene::getTiledMap());*/
	auto position = MapLayer::getObjectNodeSpace(valueMap);
	setPosition(position);
	initData(valueMap);
	initCollision(valueMap);
	return true;
}

void Actor::initData(ValueMap valueMap)
{
	SET_DATA(valueMap, CanBeHurt, Bool);
	SET_DATA(valueMap, Damage, Int);
	SET_DATA(valueMap, LocalZOrder, Int);
	auto n = VALUE_AT(valueMap, "Name", String);
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, Flag, Int);
	_HP = State(VALUE_AT(valueMap, "HP", Int));
}

void Actor::initCollision(ValueMap valueMap)
{
	if (VALUE_AT(valueMap, "Collision", Bool))
	{
		auto body = PhysicsBody::createBox(getContentSize(), defaultMaterial);
		body->SET_DATA(valueMap, Name, String);
		body->SET_DATA(valueMap, CategoryBitmask, Int);
		body->SET_DATA(valueMap, CollisionBitmask, Int);
		body->SET_DATA(valueMap, ContactTestBitmask, Int);
		body->SET_DATA(valueMap, Dynamic, Bool);
		body->SET_DATA(valueMap, RotationEnable, Bool);
		setPhysicsBody(body);
	}
}

inline void Actor::afterDead()
{
	auto body = getPhysicsBody();
	if (body)
		body->removeFromWorld();
	this->removeFromParentAndCleanup(true);
}

inline void Actor::getHurt(INT32 dmg)
{
	_HP.setStateBy(-dmg);
	if (isDead())
		afterDead();
}

inline bool Actor::isDead()
{
	return _HP.isEmpty();
}

inline void Actor::setCanBeHurt(bool num)
{
	_HP.setImmutable(!num);
}

inline bool Actor::getCanBeHurt()
{
	return !(_HP.getImmutable());
}

//Flag不一样才受伤
inline bool Actor::onContactBegin(Actor* a2)
{
	if (isAnotherFlag(a2))
	{
		getHurt(a2->_damage);
		return true;
	}
	return false;
}

//Flag不一样
inline bool Actor::isAnotherFlag(Actor* a2)
{
	return _flag != a2->getFlag();
}


//密度 弹性 摩擦力
const PhysicsMaterial Actor::defaultMaterial = PhysicsMaterial(0.0f, 0.0f, 0.0f);