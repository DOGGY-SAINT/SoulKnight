#include"MainScene.h"
#include"MapLayer.h"
#include"Component/Constant.h"
#include"Weapon/Weapon.h"
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

	//武器信息存储
	auto file = FileUtils::getInstance();
	file->addSearchPath(PATH_DATA + "WeaponData.plist");
	ValueMap weaponMap, pistolData, shotgunData, lightsaberData, hatchetData, machinegunData;
	ValueMap pistolBulletData, shotgunBulletData, lightsaberBulletData, hatchetBulletData, machinegunBulletData;
	//Pistol信息
	pistolBulletData["Damage"] = 3;
	pistolData["Name"] = "pistol";
	pistolData["Gaptime"] = 0.2;
	pistolData["BulletData"] = pistolBulletData;
	//Shotgun信息
	shotgunBulletData["Damage"] = 3;
	shotgunData["Name"] = "shotgun";
	shotgunData["Gaptime"] = 0.5;
	shotgunData["BulletData"] = shotgunBulletData;
	//Lightsaber信息
	lightsaberBulletData["Damage"] = 5;
	lightsaberData["Name"] = "lightsaber";
	lightsaberData["Gaptime"] = 0.3;
	lightsaberData["BulletData"] = lightsaberBulletData;
	//Hatchet信息
	hatchetBulletData["Damage"] = 7;
	hatchetData["Name"] = "hatchet";
	hatchetData["Gaptime"] = 0.7;
	hatchetData["BulletData"] = hatchetBulletData;
	//Machinegun信息
	machinegunBulletData["Damage"] = 2;
	machinegunData["Name"] = "hatchet";
	machinegunData["Gaptime"] = 0.1;
	machinegunData["BulletData"] = hatchetBulletData;

	weaponMap["pistol"] = pistolData;
	weaponMap["shotgun"] = shotgunData;
	weaponMap["lightsaber"] = lightsaberData;
	weaponMap["hatchet"] = hatchetData;
	weaponMap["machinegun"] = machinegunData;

	bool b=file->writeValueMapToFile(lightsaberData, PATH_DATA + "WeaponData.plist");

	/*_sharedScene = this;*/
	_myMapLayer = MapLayer::create(mapName);
	addChild(_myMapLayer);
	
	return true;
}



MainScene* MainScene::SharedScene()
{
	return static_cast <MainScene*>(Director::getInstance()->getRunningScene());
}

