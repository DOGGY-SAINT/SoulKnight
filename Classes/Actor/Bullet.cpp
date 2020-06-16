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
<<<<<<< HEAD
	
=======
>>>>>>> DOGGY_LEE
}

//不设Position，V，dir等,锚点(0.5,0.5)
bool Bullet::initByTexture(Texture2D* texture, ValueMap valueMap)
{
	if (!initWithTexture(texture))
		return false;
	initData(valueMap);
	initCollision(valueMap);
	return true;
}

<<<<<<< HEAD

=======
>>>>>>> DOGGY_LEE
