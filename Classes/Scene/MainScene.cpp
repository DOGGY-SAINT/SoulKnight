#include"MainScene.h"
#include"MapLayer.h"
#include"Component/Constant.h"
#include"Actor/Hero.h"
#include"Weapon/Weapon.h"
#include"PauseScene.h"
#include"Scene/HelloWorldScene.h"
#include"Component/State.h"

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
	initInfoLayer();
	initEnergyStrand();
	initBloodStrand();
	initArmorStrand();
	return true;
}


void MainScene::initMap(std::string mapName)
{
	_mapLayer = MapLayer::create(mapName);
	_mapLayer->setPosition(Vec2::ZERO);
	addChild(_mapLayer, MAP_LAYER);
}

void MainScene::initInfoLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto closeItem = MenuItemImage::create(
		"picture/interface/pausebutton.png",
		"picture/interface/pausebutton2.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{}
	else
	{
		closeItem->setAnchorPoint(ccp(1.0f, 1.0f));
		auto scaleTo1 = ScaleTo::create(0.5f, 0.5f);
		closeItem->runAction(scaleTo1);
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void MainScene::initHero()
{
	_hero = Hero::createWithName(DEFAULT_HERO_NAME);
	_mapLayer->addHero(_hero);
	_HPBar = _hero->getHP()->createBar("picture/interface/blood.png");
	_ACBar = _hero->getAC()->createBar("picture/interface/armor.png");
	_powerBar = _hero->getPower()->createBar("picture/interface/engery.png");
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
	contactListener->onContactSeparate = CC_CALLBACK_1(MainScene::onContactSeparate, this);
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
	mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

void MainScene::initScheduler()
{
	schedule(schedule_selector(MainScene::updateMapPosition));
	schedule(schedule_selector(MainScene::updateStateBar));
}

//保持英雄在正中央
void MainScene::updateMapPosition(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto heroPos = getHero()->getPosition();
	_mapLayer->setPosition(centre - heroPos);
}

void MainScene::onMouseDown(EventMouse *event)
{
	if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		_hero->setAttackOn();
}

void MainScene::onMouseUp(EventMouse* event) {
	if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		_hero->setAttackOff();
}

void MainScene::onMouseMove(EventMouse *event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centre = this->convertToWorldSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pos = CCDirector::sharedDirector()->convertToUI(event->getLocation());
	auto dir = pos - centre;
	_hero->getMainWeapon()->setDirection(dir);
	_hero->getMainWeapon()->updateRotation();
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
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		menuCloseCallback(nullptr);
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
	bool ret1 = false, ret2 = false;
	if (Actor1&&Actor2)
	{
		ret1 = Actor1->onContactBegin(Actor2);
		ret2 = Actor2->onContactBegin(Actor1);
		if (Actor1->isDead())
			Actor1->afterDead();
		if (Actor2->isDead())
			Actor2->afterDead();
	}
	return ret1 && ret2;
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

void MainScene::gameRestart()
{
	_mapLayer->unscheduleAllCallbacks();
	releaseAllActor();
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.3f, HelloWorld::createScene()));
	retain();
	release();
}

void MainScene::changeMap(std::string mapName)
{
	_hero->setAttackOff();
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
	_hero->initController();
	Director::getInstance()->pushScene(PauseScene::createScene());

}

void MainScene::releaseAllActor()
{
	_mapLayer->addActorToVec(_hero);
	_mapLayer->addActorToVec(_hero->getMainWeapon());
	_mapLayer->releaseAllActor();
}

void MainScene::updateStateBar(float dt)
{
	auto HP = _hero->getHP();
	auto AC = _hero->getAC();
	auto power = _hero->getPower();
	_HPBar->setPercentage(HP->getPercentage());
	_ACBar->setPercentage(AC->getPercentage());
	_powerBar->setPercentage(power->getPercentage());
}

//void MainScene::onExit()
//{
//	Scene::onExit();
//	_mapLayer->releaseAllActor();
//}


void MainScene::initEnergyStrand()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto tripleBackground = Sprite::create("picture/interface/tripleBoard.png");
	float x1 = visibleSize.width-805+27;
	float y1 = visibleSize.height-125-18;
	float x2 = visibleSize.width - 790;
	float y2 = visibleSize.height - 125;
	_powerBar->setPosition(Vec2(x1, y1));
	tripleBackground->setPosition(Vec2(x2, y2));
	this->addChild(tripleBackground, 1);
	this->addChild(_powerBar, 2);
}

void MainScene::initBloodStrand()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);


	float x = visibleSize.width - 805+27;
	float y = visibleSize.height - 125 + 22;
	_HPBar->setPosition(Vec2(x, y));
	this->addChild(_HPBar, 2);
}

void MainScene::initArmorStrand()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//屏幕中心
	auto centre = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	float x = visibleSize.width - 805+27;
	float y = visibleSize.height - 125+2;
	_ACBar->setPosition(Vec2(x, y));
	this->addChild(_ACBar, 2);
}