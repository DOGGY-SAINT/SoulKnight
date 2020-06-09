#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_
#include"cocos2d.h"
class Hero;
class MapLayer;
class PauseLayer;
class TMXMap;

USING_NS_CC;
class MainScene :public Scene
{
	CC_SYNTHESIZE(EventListener*, _mouseListener, MouseListener);
	CC_SYNTHESIZE(MapLayer*, _mapLayer, MapLayer);
	CC_SYNTHESIZE(PauseLayer*, _pauseLayer, PauseLayer);

	std::function<void()> onRPredded;
private:
	void initMap(std::string mapName);

	void initHero();

	void initPhysicsWorld();

	void initListener();

	void initContactListener();

	void initKeyBoardListener();

	void initMouseListener();
public:
	static Hero* _hero;

	static MainScene* create(std::string mapName);

	static MainScene* createWithHero(std::string mapName,Hero*);

	bool initWithHero(std::string mapName, Hero*);

	static TMXTiledMap* getTiledMap();

	bool init(std::string mapName);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	bool onContactBegin(PhysicsContact& contact);

	void onMouseDown(EventMouse *event);

	void onMouseMove(EventMouse *event);
	
	void changeMap(std::string mapName);



	/*void initListener();*/

	static MainScene* SharedScene();

	/*void changeMap(std::string mapName);*/

};




#endif