#include "PistolBullet.h"
#include"cocos2d.h"
USING_NS_CC;




static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

PistolBullet::PistolBullet()
{
}


PistolBullet::~PistolBullet()
{
}
bool PistolBullet::init() {
	bulletShape = Sprite::create("PistolBullet.png");
	if (bulletShape == nullptr)
	{
		problemLoading("'fonts/bulletShape'");
		return false;
	}
	bulletAmount = 50;
	//×Óµ¯Ä£ÐÍ
	auto bullet_size = Size(bulletShape->getScaleX(), bulletShape->getScaleY());
	auto bulletBody = PhysicsBody::createEdgeBox(bullet_size, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	bulletBody->setDynamic(false);
	bulletShape->setPhysicsBody(bulletBody);
}
void PistolBullet::shootingMode() {
	
}
int PistolBullet::getBulletAmount() {
	return bulletAmount;
}
