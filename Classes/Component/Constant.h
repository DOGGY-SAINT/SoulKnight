#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define SET_DATA(mapName,dataName,typeName)\
set##dataName(mapName[#dataName].as##typeName##())

#define ADD_DATA(mapName,dataName,typeName)\
mapName.insert(Map<std::string,typeName>[#dataName].as##typeName##())

//dataName需要双引号
#define VALUE_AT(mapName,dataName,typeName)\
mapName[dataName].as##typeName##()


#define HERO_BORN Vec2(80,80)

//Flag
#define NOFLAG  0
#define MONSTER 1
#define HERO    2

//需要双引号
#define PATH_DATA             std::string("data/")
#define PATH_PICTURE_WEAPON   std::string("picture/weapon/")
#define PATH_PICTURE_BULLET   std::string("picture/bullet/")
#define PATH_PICTURE_HERO     std::string("picture/hero/")
#define PATH_MAP              std::string("map/")


#define DEFAULT_WEAPON_NAME   std::string("M2")


//catagory&contact!=0 事件发送
//catagory&collision!=0 碰撞发生

#define BULLET_CATAGORY       0b000001
#define HERO_CATAGORY         0b000010
#define WALL_CATAGORY         0b000100
#define OPEN_DOOR_CATAGORY    0b001000
#define CLOSE_DOOR_CATAGORY   0b010000
#define MONSTER_CATAGORY      0b100000

#define BULLET_COLLISION      0b111110
#define HERO_COLLISION        0b110111
#define WALL_COLLISION        0b100011
#define OPEN_DOOR_COLLISION   0b000001
#define CLOSE_DOOR_COLLISION  0b100101
#define MONSTER_COLLISION     0b110111

#define BULLET_CONTACT        0b111110
#define HERO_CONTACT          0b000001
#define WALL_CONTACT          0b000001
#define OPEN_DOOR_CONTACT     0b000001
#define CLOSE_DOOR_CONTACT    0b000001
#define MONSTER_CONTACT       0b000001






#define HERO_LAYER  5
#define MAP_LAYER 2


#endif // !Constant_H