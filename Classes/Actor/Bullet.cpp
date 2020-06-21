#include "Bullet.h"
#include "Component/Constant.h"

Bullet* Bullet::createByTexture(Texture2D* texture, ValueMap valueMap)
{
	Bullet* bullet = new(std::nothrow)Bullet;
	if (bullet && bullet->initByTexture(texture, valueMap))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

//不设Position，V，dir等,锚点(0.5,0.5)
bool Bullet::initByTexture(Texture2D* texture, ValueMap valueMap)
{
	if (!initWithTexture(texture))
		return false;
	auto file = FileUtils::getInstance();
	auto defaultMap = file->getValueMapFromFile(PATH_DATA + "BulletDefaultData.plist");
	initData(VALUE_AT(defaultMap,"CommonData",ValueMap));
	initCollision(VALUE_AT(defaultMap, "CollisionData", ValueMap));
	SET_DATA(valueMap, Damage, Int);
	return true;
}

