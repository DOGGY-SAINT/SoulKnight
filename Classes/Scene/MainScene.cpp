#include"MainScene.h"
#include"MapLayer.h"
#include"Component/Constant.h"
#include"Actor/Hero.h"
#include"Weapon/Weapon.h"
#include"PauseLayer.h"

USING_NS_CC;

MainScene* MainScene::_sharedScene = nullptr;

MainScene* MainScene::create(std::string mapName)
{
	MainScene* mainScene = new(std::nothrow)MainScene;
	if (mainScene && mainScene->init(mapName))
	{
		mainScene->autorelease();
		return mainScene;
	}
	CC_SAFE_DELETE(mainScene);
	return nullptr;
}

bool MainScene::init(std::string mapName)
{
	if (!initWithPhysics())
		return false;
	_sharedScene = this;
	initPhysicsWorld();
	initMap(mapName);
	initHero();
	initListener();
	initScheduler();
	return true;
}


void MainScene::initMap(std::string mapName)
{
	_mapLayer = MapLayer::create(mapName);
	_mapLayer->setPosition(Vec2::ZERO);
	addChild(_mapLayer,MAP_LAYER);
	////////////////////////////////////////////////////////////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto closeItem = MenuItemImage::create(
		"pausebutton.png",
		"pausebutton2.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{

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
}

void MainScene::initHero()
{
	_hero = Hero::createWithName(DEFAULT_HERO_NAME);
	_mapLayer->addHero(_hero);
}

void MainScene::initPhysicsWorld()
{
	auto world = getPhysicsWorld();
	world->setGravity(Vec2::ZERO);
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

void MainScene::initListener()
{
	initKeyBoardListener();
	initContactListener();
	initMouseListener();
}

void MainScene::initContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
	contactListener->onContactSeparate= CC_CALLBACK_1(MainScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void MainScene::initKeyBoardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MainScene::initMouseListener()
{
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

void MainScene::initScheduler()
{
	schedule(schedule_selector(MainScene::updateMapPosition));

}

//保持英雄在正中央
void MainScene::updateMapPosition(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto heroPos = getHero()->getPosition();
	_mapLayer->setPosition(centre-heroPos);
}

void MainScene::onMouseDown(EventMouse *event)
{
	gameBegin();
}

void MainScene::onMouseMove(EventMouse *event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centre = this->convertToWorldSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pos = CCDirector::sharedDirector()->convertToUI(event->getLocation());
	auto dir = pos - centre;
	_hero->getMainWeapon()->setDirection(dir);
}


void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto hero = _hero;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setWPressed(true);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero->setAPressed(true);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero->setSPressed(true);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero->setDPressed(true);
		break;
	case EventKeyboard::KeyCode::KEY_R:
		if (onRPressed)
			onRPressed();
		break;
	case EventKeyboard::KeyCode::KEY_T:
		if (onTPressed)
			onTPressed();
		break;
	}
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto hero = _hero;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setWPressed(false);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero->setAPressed(false);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero->setSPressed(false);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero->setDPressed(false);
		break;
	}
}

bool MainScene::onContactBegin(PhysicsContact & contact)
{
	auto Actor1 = dynamic_cast<Actor*>(contact.getShapeA()->getBody()->getNode());
	auto Actor2 = dynamic_cast<Actor*>(contact.getShapeB()->getBody()->getNode());
	bool ret1=false, ret2=false;
	if (Actor1&&Actor2)
	{
		ret1 = Actor1->onContactBegin(Actor2);
		ret2 = Actor2->onContactBegin(Actor1);
	}
	return ret1&&ret2;
}

bool MainScene::onContactSeparate(PhysicsContact & contact)
{
	auto Actor1 = dynamic_cast<Actor*>(contact.getShapeA()->getBody()->getNode());
	auto Actor2 = dynamic_cast<Actor*>(contact.getShapeB()->getBody()->getNode());
	bool ret1 = false, ret2 = false;
	if (Actor1&&Actor2)
	{
		ret1 = Actor1->onContactSeparate(Actor2);
		ret2 = Actor2->onContactSeparate(Actor1);
	}
	return ret1 && ret2;
}



TMXTiledMap* MainScene::getTiledMap()
{
	return SharedScene()->getMapLayer()->getTiledMap();
}

MainScene* MainScene::SharedScene()
{
	return _sharedScene;
}

void MainScene::gameBegin()
{
	_hero->release();
	initHero();
	changeMap(SAFE_MAP_NAME);
}


void MainScene::changeMap(std::string mapName)
{
	_mapLayer->releaseAllActor();
	_hero->retain();
	_mapLayer->removeFromParent();
	initMap(mapName);
	_mapLayer->addHero(_hero);
	_hero->initScheduler();
}

void MainScene::changeHero()
{
	auto hero = _hero->getHeroToOn();
	_hero->heroOff();
	hero->heroOn();
	onTPressed = nullptr;
}



void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->pushScene(PauseLayer::createScene());

}