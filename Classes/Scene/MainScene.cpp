#include"MainScene.h"
#include"MapLayer.h"
#include"Component/Constant.h"
#include"Actor/Hero.h"

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
	
	return true;
}





void MainScene::initMap(std::string mapName)
{
	_mapLayer = MapLayer::create(mapName);
	_mapLayer->setPosition(Vec2::ZERO);
	addChild(_mapLayer,MAP_LAYER);
}

void MainScene::initHero()
{
	_hero = Hero::createWithName(DEFAULT_HERO_NAME);
	_hero->retain();
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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

void MainScene::onMouseDown(EventMouse *event)
{
	
}

void MainScene::onMouseMove(EventMouse *event)
{

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
		if (onRPredded)
			onRPredded();
		break;
	}
	hero->controlVelocity();
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
	hero->controlVelocity();
}

bool MainScene::onContactBegin(PhysicsContact & contact)
{
	auto Actor1 = dynamic_cast<Actor*>(contact.getShapeA()->getBody()->getNode());
	auto Actor2 = dynamic_cast<Actor*>(contact.getShapeB()->getBody()->getNode());
	if (Actor1&&Actor2)
		return (Actor1->onContactBegin(Actor2) && Actor2->onContactBegin(Actor1));
	return false;
}

bool MainScene::onContactSeparate(PhysicsContact & contact)
{
	auto Actor1 = dynamic_cast<Actor*>(contact.getShapeA()->getBody()->getNode());
	auto Actor2 = dynamic_cast<Actor*>(contact.getShapeB()->getBody()->getNode());
	if (Actor1&&Actor2)
		return (Actor1->onContactSeparate(Actor2) && Actor2->onContactSeparate(Actor1));
	return false;
}



TMXTiledMap* MainScene::getTiledMap()
{
	return SharedScene()->getMapLayer()->getTiledMap();
}

MainScene* MainScene::SharedScene()
{
	return _sharedScene;
	/*auto scene = dynamic_cast<MainScene*>(CCDirector::sharedDirector()->getRunningScene());
	if (scene)
		return scene;
	return nullptr;*/
}


void MainScene::changeMap(std::string mapName)
{
	_hero->retain();
	_mapLayer->removeFromParent();
	initMap(mapName);
	_mapLayer->addHero(_hero);
}
