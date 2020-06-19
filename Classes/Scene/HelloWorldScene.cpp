#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#define SAFE_MAP_NAME         std::string("SafeMap")

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}


static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"picture/interface/startbutton2.png",
		"picture/interface/button2.1.jpg",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'picture/interface/startbutton2.png' and 'picture/interface/button2.1.jpg'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2 + 110;
		closeItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);


	auto label = Label::createWithTTF("Soul Knight", "fonts/Marker Felt.ttf", 56);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y - 135 + visibleSize.height - label->getContentSize().height));
		this->addChild(label, 1);
	}

	auto sprite0 = Sprite::create("picture/interface/startscene.jpg");
	if (sprite0 == nullptr)
	{
		problemLoading("'picture/interface/startscene.jpg'");
	}
	else
	{
		sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(sprite0, 1);
	}
	//ÎäÆ÷ÒôÐ§Ô¤¼ÓÔØ
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/Shotgun.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/SingleShotgun.mp3");
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(1.7f, MainScene::create("SafeMap")));

}
