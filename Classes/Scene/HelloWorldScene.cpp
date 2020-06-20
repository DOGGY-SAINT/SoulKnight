#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "Component/Constant.h"
#define SAFE_MAP_NAME         std::string("SafeMap")

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		PATH_PICTURE_INTERFACE+"startbutton2.png",
		PATH_PICTURE_INTERFACE + "button2.1.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'startbutton2.png' and 'button2.1.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2 + 110;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	// add "HelloWorld" splash screen"
	auto sprite0 = Sprite::create(PATH_PICTURE_INTERFACE + "startscene.png");
	if (sprite0 == nullptr)
	{
		problemLoading("startscene.png");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite0, 1);
	}
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(1.7f, MainScene::create("SafeMap")));
}
