#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* PauseLayer::createScene()
{
	return PauseLayer::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	///////////////
	auto musicOnSpr = Sprite::create("musicOn.png");
	auto musicOffSpr = Sprite::create("musicOff.png");
	auto musicOn = MenuItemSprite::create(musicOnSpr, musicOnSpr);
	auto musicOff = MenuItemSprite::create(musicOffSpr, musicOffSpr);
	auto musicButton = MenuItemToggle::createWithCallback([](Object* sender) {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		if (audio->isBackgroundMusicPlaying() == 1)
		{
			audio->pauseBackgroundMusic();
		}
		else
		{
			audio->resumeBackgroundMusic();
		}
	},
		musicOn, musicOff, NULL);
	musicButton->setPosition(Vec2((visibleSize.width / 2)- 600, (visibleSize.height / 2) - 475));
	auto menu2 = Menu::create(musicButton, NULL);
	this->addChild(menu2, 1);
	/////////////////////////
	auto goBackHome = MenuItemImage::create(
		"homebutton1.png",
		"homebutton2.png",
		[](Object* sender) {
		Director::getInstance()->replaceScene(CCTransitionFade::create(0.3f, HelloWorld::createScene()));
	});
	goBackHome->setPosition(Vec2((visibleSize.width / 2) -425, (visibleSize.height / 2) - 475));
	auto menu3 = Menu::create(goBackHome, NULL);
	this->addChild(menu3, 1);
	////////////////
	auto closeItem = MenuItemImage::create(
		"startbutton2.png",
		"button2.1.jpg",
		CC_CALLBACK_1(PauseLayer::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'startbutton2.png' and 'button2.1.jpg'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2+75;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void PauseLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
