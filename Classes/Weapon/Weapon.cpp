#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"

//weapon����Ҫ�ֶ�release��
Weapon* Weapon::createWithName(std::string weaponName)
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

//Weapon��ʼ�������ǵ���
void Weapon::initWithValueMap(ValueMap valueMap)
{
	_on = false;
	this->retain();
	auto map = MainScene::SharedScene()->getMapLayer();
	map->addActorToVec(this);									//��ӵ�release�б�
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "WeaponDefaultData.plist");
	initData(VALUE_AT(defaultMap, "CommonData", ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Weapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + getName() + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}

//��������,��Ҫ��������λ�õ�����
void Weapon::weaponOn(MovingActor* a2)
{
	a2->setMainWeapon(this);
	_on = true;
	auto map = MainScene::SharedScene()->getMapLayer();
	map->removeActorFromVec(this);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setPosition(a2->getContentSize() / 2);
	//������
	auto body = getPhysicsBody();
	body->setCategoryBitmask(WEAPON_CATAGORY);
	body->setCollisionBitmask(WEAPON_COLLISION);
	body->setContactTestBitmask(WEAPON_CONTACT);

	removeFromParent();
	a2->addChild(this);
	auto Parent = dynamic_cast<Actor*> (getParent());
	setFlag(Parent->getFlag());
}

//������������Ҫ��������λ�õ�����
void  Weapon::weaponOff()
{
	_on = false;
	auto map= MainScene::SharedScene()->getMapLayer();
	map->addActorToVec(this);
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

//�趨��delay
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

//�����ڵ���
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

//����д������ײ�ĺ������Ҵ��д�˸�
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
