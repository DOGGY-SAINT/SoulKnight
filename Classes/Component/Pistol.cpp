#include "Pistol.h"
#include"cocos2d.h"
USING_NS_CC;
using std::string;
Pistol::Pistol()
{
}


Pistol::~Pistol()
{
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Pistol::init() {
	//屏幕尺寸
	Weapon::init();
	
	//Sprite::init();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	string wn = "破旧手枪";
	weaponName = wn;
	weaponShape = Sprite::create("pistol.png");
	if (weaponShape == nullptr)
	{
		problemLoading("'fonts/weaponShape'");
		return false;
	}
	//spriteShape->setPosition(origin.x - 10, origin.y - 10);
	//this->addChild(spriteShape,2);
	/*auto bulletLable = CCLabelTTF::create("Bullet Amount:", "Arial", 14);
	if (bulletLable == nullptr)
	{
		problemLoading("'fonts/bulletLable'");
		return false;
	}*/
	//bulletLable->setPosition(visibleSize.width - 50, 0);
	//this->addChild(bulletLable, 1);
	return true;
}
void Pistol::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	weaponShape->setPosition(origin.x - 10, origin.y - 10);
}
/*void Pistol::onMouseMove(EventMouse *e)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = this->convertToWorldSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto gun = this->getChildByName("map")->getChildByName("hero")->getChildByName("gun");
	auto pos = CCDirector::sharedDirector()->convertToUI(e->getLocation());
	auto dir = pos - centre;

	auto Point = this->getChildByName("Point");
	Point->setPosition(pos);

	//show(centre, this);
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	gun->runAction(rt);
}*/
Vec2 Pistol::getWeaponPos() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 p(origin.x - 10, origin.y - 10);
	return p;
}