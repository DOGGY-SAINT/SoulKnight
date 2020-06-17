#include "Weapon.h"
#include"Actor/Hero.h"
#include "Component\Constant.h"
#include"Scene/MainScene.h"
#include"Scene/MapLayer.h"

/*Weapon* Weapon::createWithName(std::string weaponName)
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

void Weapon::initWithValueMap(ValueMap valueMap)
{
	SET_DATA(valueMap, Name, String);
	SET_DATA(valueMap, GapTime, Float);
	initBulletData(valueMap);
}


void Weapon::initBulletData(ValueMap valueMap)
{
	SET_DATA(valueMap, BulletData, ValueMap);
	auto bulletPath = PATH_PICTURE_BULLET + "Bullet" + ".png";
	setBulletTexture(_director->getTextureCache()->addImage(bulletPath));
}*/

//��������,��Ҫ��������λ�õ�����
void  Weapon::weaponOn()
{
	updateRotation();
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	Hero* myHero = runningScene->getHero();
	myHero->addChild(this);
	myHero->setMainWeapon(this);
	setFlag(myHero->getFlag());
	auto heroSize = myHero->getContentSize();
	this->setPosition(Vec2(heroSize.width / 2, heroSize.height / 2));
}

//������������Ҫ��������λ�õ�����
void  Weapon::weaponOff()
{
	this->removeFromParent();
	//��ȡ��ǰӢ�ۺͲ�
	MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMapLayer());
	Hero* myHero = runningScene->getHero();
	//��������hero�����ͼ
	myHero->setMainWeapon(NULL);
	runningLayer->addChild(this, 6);
	setPosition(myHero->getPosition());
	setDirection(Vec2(1, 0));
	updateRotation();
	//�ر�ʱ�������
	unschedule(schedule_selector(Weapon::attack));
}


//void Weapon::attack(float dt) {
	/*MainScene* runningScene = dynamic_cast<MainScene*>(Director::getInstance()->getRunningScene());
	MapLayer* runningLayer = dynamic_cast<MapLayer*>(runningScene->getMyMapLayer());
	Hero* myHero = runningLayer->getMyHero();
	if(myHero->_power>)

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
	bullet->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));*/
//}