#include "secondScene.h"

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
		sprite0->setPosition(Vec2(250, 700));

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
		sprite1->setPosition(Vec2(310, 700));

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
		sprite2->setPosition(Vec2(370, 700));

		// add the sprite as a child to this layer
		this->addChild(sprite2, 1);
	}
	// add a label shows "Hello World"
	// create and initialize a label
	auto map = TMXTiledMap::create("newmap.tmx");
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

void secondScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
