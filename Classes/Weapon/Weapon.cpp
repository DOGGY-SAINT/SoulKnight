#include "Weapon.h"
#include"Weapon/Shotgun.h"
#include"Weapon/SingleShotgun.h"
#include"Weapon/MeleeWeapon.h"
#include"Actor/Hero.h"
#include"Actor/MovingActor.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"

Weapon* Weapon::createWithName(std::string weaponName)
{
	auto file = FileUtils::getInstance();
	auto weaponMap = file->getValueMapFromFile(PATH_DATA + "WeaponData.plist");
	auto thisMap = weaponMap[weaponName].asValueMap();
	auto weaponType = VALUE_AT(thisMap, "weaponType", String);
	Weapon* weapon = NULL;
	WEAPON_JUDGE(weaponType, Shotgun);
	WEAPON_JUDGE(weaponType, SingleShotgun);
	WEAPON_JUDGE(weaponType, MeleeWeapon);
	if (weapon && weapon->initWithName(weaponName))
	{
		weapon->retain();
		return weapon;
	}
	CC_SAFE_DELETE(weapon);
	return nullptr;
}

//ע�⿴�ø�ʽ
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

void Weapon::initWithValueMap(ValueMap valueMap)
{
	/*_on = false;
	this->retain();
	auto map = MainScene::SharedScene()->getMapLayer();
	map->addActorToVec(this);									//��ӵ�release�б�
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "WeaponDefaultData.plist");
	initData(VALUE_AT(defaultMap, "CommonData", ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));

	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);*/
}


void Weapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

//��������,��Ҫ��������λ�õ�����
void  Weapon::weaponOn(MovingActor* myHero)
{
//<<<<<<< HEAD
//	a2->setMainWeapon(this);
	_on = true;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->removeActorFromVec(this);

	//������
	auto body = getPhysicsBody();
	body->setCategoryBitmask(WEAPON_CATAGORY);
	body->setCollisionBitmask(WEAPON_COLLISION);
	body->setContactTestBitmask(WEAPON_CONTACT);
//
	removeFromParent();
//	a2->addChild(this);
//	auto Parent = dynamic_cast<Actor*> (getParent());
//	setFlag(Parent->getFlag());
//=======
	updateRotation();
	myHero->addChild(this);
	myHero->setMainWeapon(this);
	setFlag(myHero->getFlag());
	auto heroSize = myHero->getContentSize();
	this->setPosition(Vec2(heroSize.width / 2-10, heroSize.height / 2-10));
//>>>>>>> Kite
}

//������������Ҫ��������λ�õ�����
void  Weapon::weaponOff()
{
//<<<<<<< HEAD
//	_on = false;
//	auto map = MainScene::SharedScene()->getMapLayer();
//	map->addActorToVec(this);
//	auto pos = map->convertToNodeSpace(convertToWorldSpace(getPosition()));
//	removeFromParent();
//	map->addChild(this);
//	setPosition(pos);
//=======
	_on = false;
	removeFromParent();
	//��ȡ��ǰӢ�ۺͲ�
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	Hero* myHero = runningScene->getHero();
	auto pos = runningLayer->convertToNodeSpace(convertToWorldSpace(getPosition()));
	//��������hero�����ͼ
	myHero->setMainWeapon(NULL);
	runningLayer->addChild(this, 6);
	setPosition(pos);
//>>>>>>> Kite
	setDirection(Vec2(1, 0));
	updateRotation();
	//�ر�ʱ�������
	unschedule(schedule_selector(Weapon::attack));
}


void Weapon::attack(float dt) {
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	Hero* myHero = runningScene->getHero();
	//if(myHero->_power>)

	auto bullet = Sprite::createWithTexture(getBulletTexture());

	//�ӵ�ģ��
	auto bulletSize = getContentSize();
	auto bulletBody = PhysicsBody::createEdgeBox(bulletSize, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody->setDynamic(false);
	bullet->setPhysicsBody(bulletBody);

	//�ӵ�λ�úͽǶ�
	auto weaponSize = getContentSize();
	auto dir = getDirection();
	auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
	auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	bullet->runAction(rt);
	auto weaponPosition = getPosition();

	runningLayer->addChild(bullet, 6);
	
	bullet->setPosition(weaponPosition.x + cos * weaponSize.width / 2, weaponPosition.y + sin * weaponSize.height / 2);
	bullet->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
}