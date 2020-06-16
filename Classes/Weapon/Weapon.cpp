#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"

<<<<<<< HEAD
/*Weapon* Weapon::createWithName(std::string weaponName)
=======
//weapon是需要手动release的
Weapon* Weapon::createWithName(std::string weaponName)
>>>>>>> DOGGY_LEE
{
	Weapon* weapon = new(std::nothrow)Weapon;
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->autorelease();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//注意看好格式
bool Weapon::initWithName(std::string weaponName)
{
	if (!initWithFile(PATH_PICTURE_WEAPON + weaponName + ".png"))
		return false;
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	initWithValueMap(thisMap);
	return true;
}

<<<<<<< HEAD
void Weapon::initWithValueMap(ValueMap valueMap)
{
=======
//Weapon初始化掩码是道具
void Weapon::initWithValueMap(ValueMap valueMap)
{
	_on = false;
	this->retain();
	auto map = MainScene::SharedScene()->getMapLayer();
	map->addWeaponToVec(this);									//添加到release列表
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "WeaponDefaultData.plist");
	initData(VALUE_AT(defaultMap, "CommonData", ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));
>>>>>>> DOGGY_LEE
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Weapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
<<<<<<< HEAD
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}*/

//拿上武器,还要考虑设置位置的事情
void  Weapon::weaponOn()
{
	updateRotation();
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMyMapLayer());
	Hero* myHero = runningLayer->getMyHero();
	myHero->addChild(this);
	myHero->setWeapon1(this);
	setFlag(myHero->getFlag());
	auto heroSize = myHero->getContentSize();
	this->setPosition(Vec2(heroSize.width / 2, heroSize.height / 2));
=======
	auto bulletPath = PATH_PICTURE_BULLET + getName() + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

//拿上武器,还要考虑设置位置的事情
void Weapon::weaponOn(MovingActor* a2)
{
	a2->setMainWeapon(this);
	_on = true;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->removeWeaponFromVec(this);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setPosition(a2->getContentSize() / 2);
	//换掩码
	auto body = getPhysicsBody();
	body->setCategoryBitmask(WEAPON_CATAGORY);
	body->setCollisionBitmask(WEAPON_COLLISION);
	body->setContactTestBitmask(WEAPON_CONTACT);

	removeFromParent();
	a2->addChild(this);
	auto Parent = dynamic_cast<Actor*> (getParent());
	setFlag(Parent->getFlag());
>>>>>>> DOGGY_LEE
}

//换下武器，还要考虑设置位置的事情
void  Weapon::weaponOff()
{
<<<<<<< HEAD
	this->removeFromParent();
	//获取当前英雄和层
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMyMapLayer());
	Hero* myHero = runningLayer->getMyHero();
	//将武器从hero移向地图
	myHero->setWeapon1(NULL);
	runningLayer->addChild(this, 6);
	setPosition(myHero->getPosition());
	setDirection(Vec2(1, 0));
	updateRotation();
	//关闭时间调度器
	unschedule(schedule_selector(Weapon::attack));
}


//void Weapon::attack(float dt) {
	/*MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMyMapLayer());
	Hero* myHero = runningLayer->getMyHero();
	if(myHero->_power>)

	auto bullet = Sprite::createWithTexture(getBulletTexture());

	//子弹模型
	auto bulletSize = getContentSize();
	auto bulletBody = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody->setDynamic(false);
	bullet->setPhysicsBody(bulletBody);

	//子弹位置和角度
	auto weaponSize = getContentSize();
	auto dir = getDirection();
	auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	bullet->runAction(rt);
	auto weaponPosition = getPosition();

	runningLayer->addChild(bullet, 6);
	
	bullet->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.height / 2);
	bullet->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));*/
//}
=======
	_on = false;
	auto map= MainScene::SharedScene()->getMapLayer();
	map->addWeaponToVec(this);
	auto pos = map->convertToNodeSpace(convertToWorldSpace(getPosition()));
	removeFromParent();
	map->addChild(this);
	setPosition(pos);
	setDirection(Vec2(1, 0));

	auto body = getPhysicsBody();
	body->setCategoryBitmask(PROP_CATAGORY);
	body->setCollisionBitmask(PROP_COLLISION);
	body->setContactTestBitmask(PROP_CONTACT);

	unschedule(schedule_selector(Weapon::attack));
}

//设定了delay
void Weapon::onLeftPressed()
{
	schedule(schedule_selector(Weapon::attack), _gapTime, CC_REPEAT_FOREVER, _gapTime);

}

void Weapon::onLeftReleased()
{
	unschedule(schedule_selector(Weapon::attack));
}

bool Weapon::onContactBegin(Actor *a2)
{
	if (_on)
		return weaponOnContact(a2);
	else
		return weaponOffContact(a2);
}

//武器在地上
bool Weapon::weaponOffContact(Actor *a2)
{
	if (a2->getName() == "Hero")
	{
		auto hero = MainScene::SharedScene()->getHero();
		hero->setWeaponToOn(this);
		MainScene::SharedScene()->onTPressed = CC_CALLBACK_0(Hero::changeWeapon, hero);
	}
	return false;
}

//这里写刀子碰撞的函数，我大概写了个
bool Weapon::weaponOnContact(Actor *a2)
{
	if (isAnotherFlag(a2) && (a2->getFlag() != FLAG_NOHURT))
	{
		getHurt(a2->getDamage());
	}
	return false;
}

void Weapon::setDirection(Vec2 dir)
{
	_direction = dir;
	updateRotation();
}


void Weapon::updateRotation()
{
	setRotation(-CC_RADIANS_TO_DEGREES(_direction.getAngle()));
}
>>>>>>> DOGGY_LEE
