#include"MainScene.h"
#include"MapLayer.h"
#include"Component/Constant.h"

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
	/*_sharedScene = this;*/
	_myMapLayer = MapLayer::create(mapName);
	addChild(_myMapLayer);
	return true;
}



MainScene* MainScene::SharedScene()
{
	return static_cast <MainScene*>(Director::getInstance()->getRunningScene());
}

