#include "secondScene.h"
#include "PauseLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
	map->setAnchorPoint(ccp(0.5f, 0.5f));
	map->setPosition(Point(450, 450));
	addChild(map, 0);

	return true;
}

void secondScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->pushScene(PauseLayer::createScene());
//	Director::getInstance()->replaceScene(CCTransitionFade::create(1.7f, PauseLayer::createScene()));

}
