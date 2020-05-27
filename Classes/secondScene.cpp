#include "secondScene.h"
<<<<<<< HEAD
#include "PauseLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
=======
#include "Component/Pistol.h"
#include "Component/PistolBullet.h"
#include "SimpleAudioEngine.h"
#include "math.h"
#include "stdlib.h"
#include"cocos2d.h"
>>>>>>> Kite
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
<<<<<<< HEAD
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
=======
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//预加载音乐
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("pistolmusic.wav");

	//时间调试器
	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	if (!Scene::init())
	{
		return false;
	}

	//手枪
	auto pistol = Pistol::create();
	pistol->weaponShape->setPosition(centre);
	pistol->weaponShape->setName("pistol");
	this->addChild(pistol->weaponShape,1);

	//子弹
	auto pistolBullet = PistolBullet::create();
	pistolBullet->setName("pistolBullet");
	this->addChild(pistolBullet);

	//子弹框
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

	//鼠标移动
	auto l2 = EventListenerMouse::create();
	l2->onMouseMove = CC_CALLBACK_1(secondScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(l2, this);

	//鼠标左键按下
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT&&pistolBullet->bulletAmount>0) {
			//由于schedule的机制，另外输出第一颗子弹
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

			//更新子弹数
			pistolBullet->bulletAmount--;
			string str2 = "BulletAmount:";
			str2 += to_string(pistolBullet->bulletAmount);
			bulletLable->setString(str2);

			//进行schedule循环
			schedule(schedule_selector(secondScene::onMousePressed), 0.2f);
		}
	};

	//鼠标左键松开
	listener->onMouseUp = [=](EventMouse* event) {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			unschedule(schedule_selector(secondScene::onMousePressed));
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
>>>>>>> Kite

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(secondScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
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
<<<<<<< HEAD
	map->setAnchorPoint(ccp(0.5f, 0.5f));
	map->setPosition(Point(450, 450));
	addChild(map, 0);

	return true;
}

void secondScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->pushScene(PauseLayer::createScene());
//	Director::getInstance()->replaceScene(CCTransitionFade::create(1.7f, PauseLayer::createScene()));
=======
	map->setAnchorPoint(ccp(-0.07f, 0.02f));
	addChild(map, 0);


	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("smallmap.png");
//	if (sprite == nullptr)
	//{
	//	problemLoading("'smallmap.png'");
	//}
	//else
	//{
	//	// position the sprite on the center of the screen
///		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//
		//// add the sprite as a child to this layer
		//this->addChild(sprite, 0);
	//}


	return true;
}


void secondScene::update(float dt) {
	
}


void secondScene::onMousePressed(float dt) {
	    //输出子弹
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

		//更新子弹数
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
	//屏幕中心
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
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
>>>>>>> Kite

}
