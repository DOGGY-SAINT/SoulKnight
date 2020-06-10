#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "secondScene.h"

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
	
	/////////////////////////
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
		float y = visibleSize.height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto tmp1 = Label::createWithTTF("Soul Knight", "fonts/Marker Felt.ttf",56);
	auto tmp2 = MenuItemFont::create("Off");
	//tmp1->setFontName("fonts / Marker Felt.ttf");
	auto les = MenuItemToggle::createWithCallback( [](Object* sender) {
		auto audio = SimpleAudioEngine::getInstance();

		if (audio->isBackgroundMusicPlaying()==1)
		{
			audio->pauseBackgroundMusic();
		}
		else
		{
			audio->resumeBackgroundMusic();
		}
	},
		tmp1,tmp2, NULL);

	les->setPosition(200, 200);
	
		
	auto volumeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Object* sender) {
		auto audio = SimpleAudioEngine::getInstance();
	
	//	auto vol = audio->getBackgroundMusicVolume();
		audio->setBackgroundMusicVolume( 0.0);
		
		// your code here
	});
	volumeItem->setPosition(100,100);
	auto menu2 = Menu::create(volumeItem,les, NULL);
	this->addChild(menu2, 1);

	return true;
}


void PauseLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();

}
