#include "secondScene.h"
#include "Component/Pistol.h"
#include "Component/PistolBullet.h"
#include "SimpleAudioEngine.h"
#include "math.h"
#include "stdlib.h"
#include"cocos2d.h"
#include"PauseLayer.h"

USING_NS_CC;

Scene* secondScene::createScene()
{
	return secondScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool secondScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//Ԥ��������
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("pistolmusic.wav");

	//ʱ�������
	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//��Ļ����
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	if (!Scene::init())
	{
		return false;
	}

	//��ǹ
	auto pistol = Pistol::create();
	pistol->weaponShape->setPosition(centre);
	pistol->weaponShape->setName("pistol");
	this->addChild(pistol->weaponShape,1);

	//�ӵ�
	auto pistolBullet = PistolBullet::create();
	pistolBullet->setName("pistolBullet");
	this->addChild(pistolBullet);

	//�ӵ���
	string str = "BulletAmount:";
	str += to_string(pistolBullet->bulletAmount);
	auto bulletLable = CCLabelTTF::create(str, "Arial", 20);
	if (bulletLable == nullptr)
	{
		problemLoading("'fonts/bulletLable'");
		return false;
	}
	bulletLable->setName("Lable");
	bulletLable->setPosition(visibleSize.width - 100, 20);
	this->addChild(bulletLable, 1);
	//
	auto bloodbackground = Sprite::create("bloodbackground.jpg");
	if (bloodbackground == nullptr)
	{
		problemLoading("'bloodbackground.jpg'");
		return false;
	}
	bloodbackground->setName("bloodbackground");
	bloodbackground->setPosition(Vec2(150, 750));
	bloodbackground->setAnchorPoint(ccp(0.00001f, 0.5f));
	this->addChild(bloodbackground, 1);
	//����
	auto bloodsqu = Sprite::create("engery.png");
	if (bloodsqu == nullptr)
	{
		problemLoading("'engery.jpg'");
		return false;
	}
	bloodsqu->setName("bloodsqu");
	bloodsqu->setPosition(Vec2(150, 750));
	bloodsqu->setAnchorPoint(ccp(0.00001f, 0.5f));
	this->addChild(bloodsqu, 1);
	//����ƶ�
	auto l2 = EventListenerMouse::create();
	l2->onMouseMove = CC_CALLBACK_1(secondScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(l2, this);

	//����������
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT&&pistolBullet->bulletAmount>0) {
			//����schedule�Ļ��ƣ����������һ���ӵ�
			CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
			auto pistolbullet = PistolBullet::create();
			auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
			auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
			auto pistol_size = this->getChildByName("pistol")->getContentSize();
			auto pistolPosition = this->getChildByName("pistol")->getPosition();
			pistolbullet->bulletShape->runAction(rt);
			pistolbullet->bulletShape->setPosition(pistolPosition.x + cos * pistol_size.width / 2, pistolPosition.y + sin * pistol_size.height / 2);
			if (pistolbullet->bulletShape == nullptr) {
				problemLoading("'copy bulletShape.png'");
			}
			else {
				this->addChild(pistolbullet->bulletShape, 1);
				SimpleAudioEngine::sharedEngine()->playEffect("pistolmusic.wav");
				pistolbullet->bulletShape->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
			}

			//�����ӵ���
			pistolBullet->bulletAmount--;
			string str2 = "BulletAmount:";
			str2 += to_string(pistolBullet->bulletAmount);
			bulletLable->setString(str2);

			//auto bloodsqu = dynamic_cast<Sprite*>(this->getChildByName("bloodsqu"));
			auto scaleBy = ScaleBy::create(0.1f, (float)pistolBullet->bulletAmount/((float)pistolBullet->bulletAmount+1), 1.0f);
			bloodsqu->runAction(scaleBy);
			//����scheduleѭ��
			
			schedule(schedule_selector(secondScene::onMousePressed), 0.2f);
		}
	};

	//�������ɿ�
	listener->onMouseUp = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			unschedule(schedule_selector(secondScene::onMousePressed));
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"pausebutton.png",
		"pausebutton2.png",
		CC_CALLBACK_1(secondScene::menuCloseCallback, this));
	
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'pausebutton.png' and 'pausebutton2.png'");
	}
	else
	{
		closeItem->setAnchorPoint(ccp(1.0f, 1.0f));
		auto scaleTo1 = ScaleTo::create(0.5f, 0.5f);
		closeItem->runAction(scaleTo1);
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto sprite0 = Sprite::create("heart3.png");
	if (sprite0 == nullptr)
	{
		problemLoading("'heart3.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite0->setPosition(Vec2(150, 700));

		// add the sprite as a child to this layer
		this->addChild(sprite0, 1);
	}
	//////////
	auto sprite1 = Sprite::create("heart3.1.png");
	if (sprite1 == nullptr)
	{
		problemLoading("'heart3.1.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite1->setPosition(Vec2(190, 700));

		// add the sprite as a child to this layer
		this->addChild(sprite1, 1);
	}
	///////
	auto sprite2 = Sprite::create("heart3.2.png");
	if (sprite2 == nullptr)
	{
		problemLoading("'heart3.2.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite2->setPosition(Vec2(230, 700));

		// add the sprite as a child to this layer
		this->addChild(sprite2, 1);
	}
	// add a label shows "Hello World"
	// create and initialize a label
	auto map = TMXTiledMap::create("newmap.tmx");
	map->setAnchorPoint(ccp(-0.07f, 0.02f));
	addChild(map, 0);

	return true;
}

void secondScene::update(float dt) {
	
	//����scheduleѭ��
	
}


void secondScene::onMousePressed(float dt) {
	    //����ӵ�
	auto bulletInstence = dynamic_cast<PistolBullet*>(this->getChildByName("pistolBullet"));
	if (bulletInstence->bulletAmount > 0) {
		CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
		auto pistolbullet = PistolBullet::create();
		auto sin = dir.y / sqrt(dir.x*dir.x + dir.y*dir.y);
		auto cos = dir.x / sqrt(dir.x*dir.x + dir.y*dir.y);
		auto pistol_size = this->getChildByName("pistol")->getContentSize();
		auto pistolPosition = this->getChildByName("pistol")->getPosition();
		pistolbullet->bulletShape->runAction(rt);
		pistolbullet->bulletShape->setPosition(pistolPosition.x + cos * pistol_size.width / 2, pistolPosition.y + sin * pistol_size.height / 2);
		if (pistolbullet->bulletShape == nullptr) {
			problemLoading("'copy bulletShape.png'");
		}
		else {
			this->addChild(pistolbullet->bulletShape, 1);
			SimpleAudioEngine::sharedEngine()->playEffect("pistolmusic.wav");
			pistolbullet->bulletShape->getPhysicsBody()->setVelocity(Vec2(100 * cos, 100 * sin));
		}

		//�����ӵ���
		bulletInstence->bulletAmount--;
		string str = "BulletAmount:";
		str += to_string(bulletInstence->bulletAmount);
		auto bulletLable = dynamic_cast<CCLabelTTF*>(this->getChildByName("Lable"));
		bulletLable->setString(str);
		
	}
}
void secondScene::onMouseMove(EventMouse *e)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//��Ļ����
	auto centre = this->convertToWorldSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto gun = this->getChildByName("pistol");
	auto pos = CCDirector::sharedDirector()->convertToUI(e->getLocation());
	dir = pos - centre;

	/*show(centre, this);*/
	CCRotateTo* rt = CCRotateTo::create(0, -CC_RADIANS_TO_DEGREES(dir.getAngle()));
	gun->runAction(rt);
}


void secondScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->pushScene(PauseLayer::createScene());


}
