#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_
#include"cocos2d.h"
class Hero;
class MapLayer;
class PauseLayer;


USING_NS_CC;
class MainScene :public Scene
{
private:
	/*static MainScene *_sharedScene;*/
	CC_SYNTHESIZE(EventListener*, _mouseListener, MouseListener);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(MapLayer*, _myMapLayer, MyMapLayer);
	CC_SYNTHESIZE(PauseLayer*, _myPauseLayer, MyPauseLayer);

	
public:
	static MainScene* create(std::string mapName);

	bool init(std::string mapName);

	/*void initListener();*/

	static MainScene* SharedScene();

	/*void changeMap(std::string mapName);*/

};

//MainScene* MainScene::_sharedScene = nullptr;


#endif