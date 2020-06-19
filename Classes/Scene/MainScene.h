#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_
#include"cocos2d.h"
class Hero;
class MapLayer;
class PauseScene;
class TMXMap;
class Actor;

USING_NS_CC;
class MainScene :public Scene
{
	CC_SYNTHESIZE(EventListener*, _mouseListener, MouseListener);
	CC_SYNTHESIZE(MapLayer*, _mapLayer, MapLayer);
	CC_SYNTHESIZE(PauseScene*, _pauseLayer, PauseScene);
	CC_SYNTHESIZE(Hero*, _hero, Hero);
private:

	void initMap(std::string mapName);

	void initInfoLayer();

	void initHero();

	void initPhysicsWorld();

	void initListener();

	void initContactListener();

	void initKeyBoardListener();

	void initMouseListener();

	void initScheduler();

	void updateMapPosition(float dt);
public:
	static MainScene* _sharedScene;

	//捡道具，传送门
	std::function<void()> onRPressed;
	//换枪
	std::function<void()> onTPressed;

	static MainScene* create(std::string mapName);

	static TMXTiledMap* getTiledMap();

	bool init(std::string mapName);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	bool onContactBegin(PhysicsContact& contact);

	bool onContactSeparate(PhysicsContact& contact);

	void onMouseDown(EventMouse *event);

	void onMouseUp(EventMouse *event);

	void onMouseMove(EventMouse *event);
	
	void changeMap(std::string mapName);

	void changeHero();

	static MainScene* SharedScene();

	void gameRestart();

	/*void changeMap(std::string mapName);*/
	void menuCloseCallback(cocos2d::Ref* pSender);

	void releaseAllActor();


};




#endif