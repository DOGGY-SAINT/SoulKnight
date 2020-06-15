#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define SET_DATA(mapName,dataName,typeName)\
set##dataName(mapName[#dataName].as##typeName##())

//dataName��Ҫ˫����
#define VALUE_AT(mapName,dataName,typeName)\
mapName[dataName].as##typeName##()



#define HERO_BORN Vec2(80,80)

//Flag
#define FLAG_NOTHING  0
#define FLAG_MONSTER 1
#define FLAG_HERO    2

//��Ҫ˫����
#define PATH_DATA             std::string("data/")
#define PATH_PICTURE_WEAPON   std::string("picture/weapon/")
#define PATH_PICTURE_BULLET   std::string("picture/bullet/")
#define PATH_PICTURE_HERO     std::string("picture/hero/")
#define PATH_MAP              std::string("map/")

#define SAFE_MAP_NAME         std::string("SafeMap")
#define DEFAULT_HERO_NAME     std::string("Knight")
#define DEFAULT_WEAPON_NAME   std::string("M2")


//catagory&contact!=0 �¼�����
//catagory&collision!=0 ��ײ����

#define BULLET_CATAGORY       0b0000000001
#define HERO_CATAGORY         0b0000000010
#define WALL_CATAGORY         0b0000000100
#define OPEN_DOOR_CATAGORY    0b0000001000
#define CLOSE_DOOR_CATAGORY   0b0000010000
#define MONSTER_CATAGORY      0b0000100000
#define PROP_CATAGORY         0b0001000000		//���е��ߣ������ţ����ӣ�ҩƿ

#define BULLET_COLLISION      0b0000111110
#define HERO_COLLISION        0b0001110111
#define WALL_COLLISION        0b0000100011
#define OPEN_DOOR_COLLISION   0b0000000001
#define CLOSE_DOOR_COLLISION  0b0000100101
#define MONSTER_COLLISION     0b0000110111
#define PROP_COLLISION        0b0000000000

#define BULLET_CONTACT        0b0000111110
#define HERO_CONTACT          0b0001000001
#define WALL_CONTACT          0b0000000001
#define OPEN_DOOR_CONTACT     0b0000000001
#define CLOSE_DOOR_CONTACT    0b0000000001
#define MONSTER_CONTACT       0b0000000001
#define PROP_CONTACT          0b0000000010






#define HERO_LAYER  5
#define MAP_LAYER 2


#endif // !Constant_H